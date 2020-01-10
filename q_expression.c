#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"
#ifdef _WIN32 // 预处理做环境判断, windows环境下使用自己实现的函数
#include <string.h>

static char buffer[2048]; // 定义一个固定大小的数组缓冲区

char *readline(char *prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);

    char *cpy = malloc(strlen(buffer)+1); // 预先开辟堆区内存(size：buffer char个数加1bit)
    strcpy(cpy, buffer); // 将buffer指针变量所指向的字符串复制到cpy指针变量所指向的空间去，为防止堆区内存缓冲溢出的错误，开辟内存加1
    cpy[strlen(cpy) - 1] = '\0'; //将cpy指针变量最后一位地址作为字符串结束符（其实strcpy会把字符串结束符'0\'复制过去）
    return cpy; // 将cpy字符串作为返回值
}

void add_history(char *unused) {} // 暂时不实现

#else // linux环境下就调用readline库
#include <readline/readline.h>
#include <readline/history.h>
#endif
#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del(args); return lval_err(err); } // LASSERT断言预处理宏, 这样宏可以在编译时对代码进行分析检查，并返回错误信息
/*
typedef struct lval { // 定义一个错误处理的结构体类型
    int type; // 表示结果的类型
    long num;
    int err;
} lval;
*/
// 为了存储我们的程序，需要创建一个内部的列表结构，它将由数字、符号、和其他列表组成。在 lisp 中这种结构称为 S-Expression 。在 S-Expression 中，将开始的元素作为操作符，其后的元素作为操作的对象，然后计算都到结果。
// S-Expression 由许多其他的变量组成，因次我们将使用一个双指针变量 cell 来存储 lval* ，这就是 lval** ；
// 而且还需要记录有多少个 lval* ，用 count 作为计数器；
// 用 err 来记录错误的信息，这将使我们的报错信息更加的完整，高效。
typedef struct lval {
  int type;
  long num; // 数字
  /* Error and Symbol types have some string data */
  char* err; // 错误信息
  char* sym; // 变量
  /* Count and Pointer to a list of "lval*" */
  int count; // 子结构次数
  struct lval** cell;
} lval;

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR }; 
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM }; // 用于描述err

lval* lval_eval(lval* v); // 声明

// 通过地址来代替实际的数据，我们可以通过函数来获取和修改地址，这比直接拷贝数据要好很多，地址只是数字，它比记录数据更省资源，在内存资源固定的情况下，更高效的使用它们显得很重要。指针重构代码
// 指针使用 * 来表示，并通过 -> 来获取取变量的元素值，变量可以通过 & 来获取自己的地址。
/*
lval lval_num(long x) { // 定义lval结构体变量函数
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

lval lval_err(int x) { // 定义lval结构体变量函数
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}
*/
/* lval构造器 */
//指针指向一个新的数字
lval* lval_num(long x) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_NUM;
  v->num = x;
  return v;
}

//指针指向一个 error
lval* lval_err(char* m) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_ERR;
  v->err = malloc(strlen(m) + 1);
  strcpy(v->err, m);
  return v;
}

//指针指向一个新的 Symbol
lval* lval_sym(char* s) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SYM;
  v->sym = malloc(strlen(s) + 1);
  strcpy(v->sym, s);
  return v;
}

//指针指向一个新的 Sexpr
lval* lval_sexpr(void) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

//指针指向一个新的 Qexpr
lval* lval_qexpr(void) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_QEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

//用于释放lval的内存资源，防止内存泄漏
void lval_del(lval* v) {

  switch (v->type) {
    /* Do nothing special for number type */
    case LVAL_NUM: break;

    /* For Err or Sym free the string data */
    case LVAL_ERR: free(v->err); break;
    case LVAL_SYM: free(v->sym); break;

    /* If Sexpr then delete all elements inside */
    case LVAL_QEXPR:
    case LVAL_SEXPR:
      for (int i = 0; i < v->count; i++) {
        lval_del(v->cell[i]);
      }
      /* Also free the memory allocated to contain the pointers */
      free(v->cell);
    break;
  }

  /* Free the memory allocated for the "lval" struct itself */
  free(v);
}

// 输出表达式
void lval_print(lval* v);

void lval_expr_print(lval* v, char open, char close) {
  putchar(open);
  for (int i = 0; i < v->count; i++) {

    /* Print Value contained within */
    lval_print(v->cell[i]);

    /* Don't print trailing space if last element */
    if (i != (v->count-1)) {
      putchar(' ');
    }
  }
  putchar(close);
}

void lval_print(lval* v) {
  switch (v->type) {
    case LVAL_NUM:   printf("%li", v->num); break;
    case LVAL_ERR:   printf("Error: %s", v->err); break;
    case LVAL_SYM:   printf("%s", v->sym); break;
    case LVAL_SEXPR: lval_expr_print(v, '(', ')'); break;
    case LVAL_QEXPR: lval_expr_print(v, '{', '}'); break;
  }
}

void lval_println(lval* v) { lval_print(v); putchar('\n'); }

int number_of_nodes(mpc_ast_t *t){ // 递归解析mpc_ast_t数据结构体
  if(t->children_num == 0){ return 1;}
  if(t->children_num >= 1){
      int total = 1;
      for (int i=0;i<t->children_num;i++)
      {
          total = total + number_of_nodes(t->children[i]);
    }
    return total;
}
    return 0;
    /*实际上这句没有必要*/
}

// 阅读表达式
lval* lval_read_num(mpc_ast_t *t) {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err("Invalid number");
}

// 用于添加新的 S-Expression
lval* lval_add(lval* v, lval* x) {
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * v->count); // realloc重新分配内存空间
  v->cell[v->count-1] = x;
  return v;
}

lval* lval_read(mpc_ast_t *t) {
    /* If Symbol or Number return conversion to that type */
    if (strstr(t->tag, "number")) { return lval_read_num(t); }
    if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

    /* If root (>) or sexpr then create empty list */
    lval* x = NULL;
    if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
    if (strstr(t->tag, "sexpr"))  { x = lval_sexpr(); }
    if (strstr(t->tag, "qexpr"))  { x = lval_qexpr(); }

    /* Fill this list with any valid expression contained within */
    for (int i = 0; i < t->children_num; i++) {
        if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "}") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "{") == 0) { continue; }
        if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }
        x = lval_add(x, lval_read(t->children[i]));
    }

    return x;
}

// 函数表达式(内建方法)
// 回收内存资源
lval* lval_pop(lval* v, int i) {
  /* Find the item at "i" */
  lval* x = v->cell[i];

  /* Shift memory after the item at "i" over the top */
  memmove(&v->cell[i], &v->cell[i+1],
    sizeof(lval*) * (v->count-i-1)); // memmove用于拷贝字节

  /* Decrease the count of items in the list */
  v->count--;

  /* Reallocate the memory used */
  v->cell = realloc(v->cell, sizeof(lval*) * v->count); // realloc重新分配内存空间
  return x;
}

//计算出错了调用
lval* lval_take(lval* v, int i) {
  lval* x = lval_pop(v, i);
  lval_del(v);
  return x;
}

// s_expression表达式---内建函数op(+-*/)
lval* builtin_op(lval* a, char* op) {

  /* Ensure all arguments are numbers */
  for (int i = 0; i < a->count; i++) {
    if (a->cell[i]->type != LVAL_NUM) {
      lval_del(a);
      return lval_err("Cannot operate on non-number!");
    }
  }

  /* Pop the first element */
  lval* x = lval_pop(a, 0);

  /* If no arguments and sub then perform unary negation */
  if ((strcmp(op, "-") == 0) && a->count == 0) {
    x->num = -x->num;
  }

  /* While there are still elements remaining */
  while (a->count > 0) {

    /* Pop the next element */
    lval* y = lval_pop(a, 0);

    if (strcmp(op, "+") == 0) { x->num += y->num; }
    if (strcmp(op, "-") == 0) { x->num -= y->num; }
    if (strcmp(op, "*") == 0) { x->num *= y->num; }
    if (strcmp(op, "/") == 0) {
      if (y->num == 0) {
        lval_del(x); lval_del(y);
        x = lval_err("Division By Zero!"); break;
      }
      x->num /= y->num;
    }

    lval_del(y);
  }

  lval_del(a); return x;
}

// q_expression表达式---内建函数head(删除下标为 1 到最后的所有元素)
lval* builtin_head(lval* a) {
  /* Check Error Conditions */
    LASSERT(a, a->count == 1,
        "Function 'head' passed too many arguments!");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
        "Function 'head' passed incorrect type!");
    LASSERT(a, a->cell[0]->count != 0,
        "Function 'head' passed {}!");

    /* Otherwise take first argument */
    lval* v = lval_take(a, 0);

    /* Delete all elements that are not head and return */
    while (v->count > 1) { lval_del(lval_pop(v, 1)); }
    return v;
}

// q_expression表达式---内建函数tail(删除第一个元素)
lval* builtin_tail(lval* a) {
  /* Check Error Conditions */
    LASSERT(a, a->count == 1,
        "Function 'tail' passed too many arguments!");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
        "Function 'tail' passed incorrect type!");
    LASSERT(a, a->cell[0]->count != 0,
        "Function 'tail' passed {}!");

    /* Take first argument */
    lval* v = lval_take(a, 0);

    /* Delete first element and return */
    lval_del(lval_pop(v, 0));
    return v;
}

// q_expression表达式---内建函数list(将 S-Expression 转为 Q-Expression)
lval* builtin_list(lval* a) {
  a->type = LVAL_QEXPR;
  return a;
}

// q_expression表达式---内建函数eval(将 Q-Expression 转为 S-Expression)
lval* builtin_eval(lval* a) {
  LASSERT(a, a->count == 1,
    "Function 'eval' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
    "Function 'eval' passed incorrect type!");

  lval* x = lval_take(a, 0);
  x->type = LVAL_SEXPR;
  return lval_eval(x);
}

// q_expression表达式---内建函数join(检查参数里的 Q-Expressions 有没有错误，没有就将它们合并)
lval* lval_join(lval* x, lval* y);

lval* builtin_join(lval* a) {

  for (int i = 0; i < a->count; i++) {
    LASSERT(a, a->cell[i]->type == LVAL_QEXPR,
      "Function 'join' passed incorrect type.");
  }

  lval* x = lval_pop(a, 0);

  while (a->count) {
    x = lval_join(x, lval_pop(a, 0));
  }

  lval_del(a);
  return x;
}

lval* lval_join(lval* x, lval* y) {

  /* For each cell in 'y' add it to 'x' */
  while (y->count) {
    x = lval_add(x, lval_pop(y, 0));
  }

  /* Delete the empty 'y' and return 'x' */
  lval_del(y);
  return x;
}

// 调用内建函数
lval* builtin(lval* a, char* func) {
  if (strcmp("list", func) == 0) { return builtin_list(a); }
  if (strcmp("head", func) == 0) { return builtin_head(a); }
  if (strcmp("tail", func) == 0) { return builtin_tail(a); }
  if (strcmp("join", func) == 0) { return builtin_join(a); }
  if (strcmp("eval", func) == 0) { return builtin_eval(a); }
  if (strstr("+-/*", func)) { return builtin_op(a, func); }
  lval_del(a);
  return lval_err("Unknown Function!");
}

// lval_read解析output, lval_eval&lval_eval_sexpr主逻辑判断

lval* lval_eval_sexpr(lval* v) {

    /* Evaluate Children */
    for (int i = 0; i < v->count; i++) {
        v->cell[i] = lval_eval(v->cell[i]);
    }

    /* Error Checking */
    for (int i = 0; i < v->count; i++) {
        if (v->cell[i]->type == LVAL_ERR) { return lval_take(v, i); }
    }

    /* Empty Expression */
    if (v->count == 0) { return v; }

    /* Single Expression */
    if (v->count == 1) { return lval_take(v, 0); }

    /* Ensure First Element is Symbol */
    lval* f = lval_pop(v, 0);
    if (f->type != LVAL_SYM) {
        lval_del(f); lval_del(v);
        return lval_err("S-expression Does not start with symbol!");
    }

    /* Call builtin with operator */
    lval* result = builtin(v, f->sym); //调用内建函数
    lval_del(f);
    return result;
}

lval* lval_eval(lval* v) {
  /* Evaluate Sexpressions */
  if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(v); }
  /* All other lval types remain the same */
  return v;
}

// // 算术表达式
// lval eval_op(lval x, char *op, lval y) {
//     /* If either value is an error return it */
//     if (x.type == LVAL_ERR) { return x; }
//     if (y.type == LVAL_ERR) { return y; }
//     /* Otherwise do maths on the number values */
//     if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
//     if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
//     if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
//     if (strcmp(op, "/") == 0) {
//     /* If second operand is zero return error */
//         return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
//     } 

//     return lval_err(LERR_BAD_OP);
// }

// lval eval(mpc_ast_t *t) {
//     // 利用递归来分析ouput char* 长字符串tag
//     // + 1 (+ 2 4) output的到的char *
//     /*
//     >
//     regex
//     operator|char:1:1 '+'
//     expr|number|regex:1:3 '1'
//     expr|>
//         char:1:5 '('
//         operator|char:1:6 '+'
//         expr|number|regex:1:8 '2'
//         expr|number|regex:1:10 '4'
//         char:1:11 ')'
//     regex 
//     */
//     if (strstr(t->tag, "number")){
//         // return atoi(t->contents); // char *转为long长整型
//         errno = 0; // errno.h
//         long x = strtol(t->contents, NULL, 10); //strtol 函数进行字符串到数字的转换，因为可以通过检测 errno 变量确定是否转换成功。10进制
//         return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
//     }
//     char *op = t->children[1]->contents;
//     lval x = eval(t->children[2]);
//     int i = 3;
//     while (strstr(t->children[i]->tag, "expr")){
//         x = eval_op(x, op, eval(t->children[i]));
//         i++;
//     }
//     return x;
// }

/* q_expression表达式, 作为列表(数组)的表达式, 并添加一些操作方法, 在symbol解析器添加一些规则(内建方法), builtin_op其实也算是一个内建函数
list    需要一个或多个参数，并返回一个 q-expression
head    需要一个 q-expression 参数,并返回只有第一个元素的 q-expression
tail    需要一个 q-expression 参数,并返回除第一个元素余下的 q-expression
join    需要多个q-expression 参数,并返回它们的组合 q-expression
eval    需要一个 q-expression 参数，并将它进行计算
*/

int main(int argc, char *argv[]) {

    mpc_parser_t *Number    = mpc_new("number"); // 由0-9数字组成，也可以用'-'来表示负数
    mpc_parser_t *Symbol    = mpc_new("symbol"); // '+', '-', '*', 或者 '/'
    mpc_parser_t *Sexpr     = mpc_new("sexpr"); // s_expression解析式
    mpc_parser_t *Qexpr     = mpc_new("qexpr"); // q_expression解析式
    mpc_parser_t *Expr      = mpc_new("expr"); // 由一个数字或者 '(' 操作符+其它的表达式 ')', 一个表达式
    mpc_parser_t *Lispy     = mpc_new("lispy"); // 输入由操作符，一个或者多个表达式组成

    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                       \
        number   : /-?[0-9]+/ ;                                 \
        symbol   : \"list\" | \"head\" | \"tail\"               \
                | \"join\" | \"eval\" | '+' | '-' | '*' | '/' ; \
        sexpr    : '(' <expr>* ')' ;                            \
        qexpr    : '{' <expr>* '}' ;                            \
        expr     : <number> | <symbol> | <sexpr> | <qexpr> ;    \
        lispy    : /^/ <expr>* /$/ ;                            \
        ",
        Number, Symbol, Sexpr, Qexpr, Expr, Lispy);
    /* 
    第一个参数是选择标志，我们使用默认值即可，
    第二个是一个长点的字符串，它是指语法说明，包含了很多的重写规则。每一条规则都有左边的 : 和右边的 ; 组成。特殊的符号定义的规则如下所示： 
    "ab"    表示字符串 ab
    'a'        表示字符 a
    'a' 'b'    表示先有字符 a ,再有字符 b
    'a' | 'b' 表示在字符 a 和 b 之间选择一个    
    'a'*    表示有0个或多个a
    'a'+    表示至少有一个a
    <abba>    表示规则 abba
    */
    puts("Lispy Version 0.6");
    puts("Press Ctrl+c to Exit\n");

    while (1)
    {
        char *input = readline("Lispy> ");
        add_history(input);

        /* Attempt to parse the user input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            /* On success print and delete the AST */
            // mpc_ast_t* a = r.output;
            // printf("Tag: %s\n", a->tag);
            // printf("Contents: %s\n", a->contents);
            // printf("Number of children: %i\n", a->children_num);

            // mpc_ast_t* c0 = a->children[0];
            // printf("First Child Tag: %s\n", c0->tag);
            // printf("First Child Contents: %s\n", c0->contents);
            // printf("First Child Number of children: %i\n" , c0->children_num);
            // mpc_ast_print(r.output);
            // mpc_ast_delete(r.output);
            // number_of_nodes(r.output);
            // long result = eval(r.output);
            // printf("%li\n", result);
            // lval result = eval(r.output);
            // lval_println(result);
            // mpc_ast_delete(r.output);
            lval* x = lval_eval(lval_read(r.output));
            lval_println(x);
            lval_del(x);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise print and delete the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input); // 释放input内存
    }

    /* Do some parsing here... */
    mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

    return 0;
}
