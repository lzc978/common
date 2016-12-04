#include "mpc.h"

// 形容词比如是 'wow'，'many'，'such' 名词比如是 'lisp'，'language'，'c'，'book'，'build' 短语是由名词 + 形容词构成 一段 Doge 可以由 0 到多个短语构成

int main(int argc, char **argv)
{
// 我们开始尝试定义形容词和名词，为了达到这个目的，我们创建了两个解析器，用 mpc_parser_t* ，并且我们用单词 Adjective 和 Noun 来表示。我们将使用函数 mpc_or 去创建一个解析器，它将包含一些功能。通过函数 mpc_sym 来初始化我们的字符串。试着理解下面的代码。

// 建立解析器 'Ajective' 来认识这个描述
mpc_parser_t *Ajective = mpc_or(4,
    mpc_sym("wow"), mpc_sym("many"),
    mpc_sym("so"), mpc_sym("such")
);
// 建立解析器 'Noun' 去描述事物
mpc_parser_t *Noun = mpc_or(5,
    mpc_sym("lisp"), mpc_sym("language"),
    mpc_sym("book"), mpc_sym("build"),
    mpc_sym("c")
);

// 函数mpc_and, 用于指定一些必须的函数事物
// 我们输入 `Adjective` 和 `Noun` ，我们定义的解析器将调用 `mpcf_strfold` 和 `free` 函数，它们将描述如何加入或者删除这些解析器
mpc_parser_t *Phrase = mpc_and(2, mpcf_strfold, Ajective, Noun, free);

// 为了描述 `Doge` ,我们需要定义 0 个到多个必要的解析器，`mpc_many` 函数可以帮助我们做到这一点，这个函数还需要变量 `mpcf_strfold` 来描述结果是如何加在一起的：
mpc_parser_t *Doge = mpc_many(mpcf_strfold, Phrase);

/* Do some parsing here... */

// 删除解析器
mpc_delete(Doge);

return 0;
}


int main(int argc, char **argv) {

  mpc_parser_t *Adjective = mpc_new("adjective");
  mpc_parser_t *Noun      = mpc_new("noun");
  mpc_parser_t *Phrase    = mpc_new("phrase");
  mpc_parser_t *Doge      = mpc_new("doge");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                           \
      adjective : \"wow\" | \"many\"            \
                |  \"so\" | \"such\";           \
      noun      : \"lisp\" | \"language\"       \
                | \"book\" | \"build\" | \"c\"; \
      phrase    : <adjective> <noun>;           \
      doge      : <phrase>*;                    \
    ",
    Adjective, Noun, Phrase, Doge);
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

  /* Do some parsing here... */

  mpc_cleanup(4, Adjective, Noun, Phrase, Doge);

  return 0;
}
