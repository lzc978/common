/* 波兰表达式
1 + 2 + 6                            is              + 1 2 6    
6 + (2 * 9)                          is              + 6 (* 2 9)    
(10 * 2) / (4 + 2)                   is              / (* 10 2) (+ 4 2)
*/
// 我们需要制定一个描述这个符号的语法，我们可以先描述文本，之后再来理解它。首先我们观察到在波兰表达式中先是运算符，之后再是数字或者其他的表达式。因此我们可以说一个程序由一个操作符，之后跟着其它的表达式或者数字组成，更正式的表示：
/*
Program         输入由操作符，一个或者多个表达式组成
Expresssion     由一个数字或者 '(' 操作符+其它的表达式 ')'
Operation         '+', '-', '*', 或者 '/'
Number            由0-9数字组成，也可以用'-'来表示负数
*/

// 我们已经知道如何编码的大多数规则了，但是数字和程序可能会出错，因为其中可能包含了一些我们还没了解的结构，比如我们还不知道怎么去开始和结束一段输入，描述可选的字符串，或者字符串的长度内的检索。
// 这些是可以表示的，通过正则表达式。正则表达式一种为文本和数字进行表式的方法。我们的语法不能用正则表达式设计太多的规则，但是它可以做到精准的匹配和操作。这里有一些基础的规则介绍正则表达式：
/* 正则表达式
.                可以匹配任何字母
a                只能匹配字符a
[abcdef]        可以匹配在字符串中的任意一个字母
[a-f]            可以匹配在a-f里的任意一个字母
a?                字符a是可要可不要
a*                可以匹配0个到多个a
a+                可以匹配1个到多个a
^                表示匹配的开始符号
$                表示匹配的结束符号
*/

// 在 mpc 库的语法里我们可以使用正则表达式将它们放在两个 / 之间，比如我们使用 Number 的规则的时候，我们可以这样来描述 /-?[0-9]+/ 。

// 我们已经学习了如何使用 mpc 库来描述我们的波兰表达式，但是在实际运用的时候我们需要进行交互式的编程，需要使用 while 循环，不只是回应用户的输入，它实际上需要尝试解析我们解析器，可以使用 mpc 库函数来代替 printf ，它将为我们的 Lispy 增彩：
```
/* Attempt to Parse the user Input */
mpc_result_t r;
if (mpc_parse("<stdin>", input, Lispy, &r)) {
  /* On Success Print the AST */
  mpc_ast_print(r.output);
  mpc_ast_delete(r.output);
} else {
  /* Otherwise Print the Error */
  mpc_err_print(r.error);
  mpc_err_delete(r.error);
}
```
// mpc_parse 函数将结合我们的 Lispy ，输入的字符串为 input 。这段代码将解析的结果保存在 r 里，如果解析成功返回 1，解析失败返回 0。我们使用 & 在 r 之前，关于这个用法我们之后将会介绍。

// 如果我们的解析是成功的，那么 r 中就会保存相关的结构，会在 output 域中，我们可以使用 mpc_ast_print 来打印它，然后也可以使用 mpc_ast_delete 来删除相关的数据。

// 以上是抽象的语法树
// 它代表了用户输入的代码的结构。显然，这颗树主要是将输入的代码分解成数字和操作符。我们需要从这颗树上对输入的信息进行遍历和分析，从而进行运算得到结果。
// 在我们继续遍历这棵树之前，先看一下这棵树是如何定义的。如果我们看 mpc.h 的内部结构，我们可以看到一个 mpc_ast_t 的结构体，它就来自于我们的解析器：
```
typedef struct mpc_ast_t{
  char* tag;
  char* contents;
  mpc_state_t state;
  int children_num;
  struct mpc_ast_t** children;
} mpc_ast_t;
```
这里面有些结构我们需要来看一看，理解一下：
> - 第一个变量是 tag ，当我们打印出这棵树的时候，它就是这个节点的信息，它是一个字符串包含了解析这个项目的所有的规则列表，举个例子 expr | number | regex 。这个 tag 变量很重要，它让我们知道了这个节点是由什么解析规则创建的。
> - 第二个变量是 contents ,它将包含一些节点的实际信息比如 * ,(，5。你将会注意这个分支是空的，但是它的树叶可以让我们找到操作符或者数字来使用。
> - 接下来的一个变量是 state ，它是一个记录关于这个解析器处理到什么地方的工具，比如行号和列号等信息，我们一般不会直接用到它。
> - 之后的变量 children 是一个 mpc_ast_t** 类型的，它是一个双指针，它实际上没有看起来的那么复杂，我们在之后的章节会详细介绍。现在你可以简单的理解它为由很多子节点组成的列表。

// 因为这里的 mpc_ast_t* 是一个指向结构体的指针，因此访问它的元素有有一些不同，我们需要使用 -> 而不是 . ，现在对于它们区别先不提，只管好好使用就行：
```
mpc_ast_t* a = r.output;
printf("Tag: %s\n", a->tag);
printf("Contents: %s\n", a->contents);
printf("Number of children: %i\n", a->children_num);

mpc_ast_t* c0 = a->children[0];
printf("First Child Tag: %s\n", c0->tag);
printf("First Child Contents: %s\n", c0->contents);
printf("First Child Number of children: %i\n" , c0->children_num);
```
