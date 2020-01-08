#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32 // 预处理做环境判断, windows环境下使用自己实现的函数
#include <string.h>
#include "mpc.h"

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

long eval_op(long x, char *op, long y) {
    if(strcmp(op, "+") == 0){return x + y;}
    if(strcmp(op, "-") == 0){return x - y;}
    if(strcmp(op, "*") == 0){return x * y;}
    if(strcmp(op, "/") == 0){return x / y;}
    return 0;
}

long eval(mpc_ast_t *t) {
    if (strstr(t->tag, "number")){
        return atoi(t->contents);
    }
    char *op = t->children[1]->contents;
    long x = eval(t->children[2]);
    int i = 3;
    while (strstr(t->children[3]->tag, "expr")){
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}

int main(int argc, char *argv[]) {

    mpc_parser_t *Number    = mpc_new("number"); // 由0-9数字组成，也可以用'-'来表示负数
    mpc_parser_t *Operator  = mpc_new("operator"); // '+', '-', '*', 或者 '/'
    mpc_parser_t *Expr      = mpc_new("expr"); // 由一个数字或者 '(' 操作符+其它的表达式 ')', 一个表达式
    mpc_parser_t *Lispy     = mpc_new("lispy"); // 输入由操作符，一个或者多个表达式组成

    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                   \
        number   : /-?[0-9]+/ ;                             \
        operator : '+' | '-' | '*' | '/' ;                  \
        expr     : <number> | '(' <operator> <expr>+ ')' ;  \
        lispy    : /^/ <operator> <expr>+ /$/ ;             \
        ",
        Number, Operator, Expr, Lispy);
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
    puts("Lispy Version 0.2");
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
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise print and delete the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input); // 释放input内存
    }

    /* Do some parsing here... */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
