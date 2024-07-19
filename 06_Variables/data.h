/**
 * 在 main.c 中定义了 extern_，这使得在 data.h 中，extern_ 被替换为空白，从而实际定义了这些全局变量。
 * 在 scan.c 中，extern_ 被替换为 extern，从而声明了这些变量。这种方式有效地管理了全局变量的声明和定义。
 */

#ifndef extern_
    #define extern_ extern
#endif


#define TEXTLEN 512

extern_ int Line;
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;
extern_ struct token Token;
extern_ char Text[TEXTLEN + 1];