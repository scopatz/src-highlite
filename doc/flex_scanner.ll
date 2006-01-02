%{
#include "genfun.h"

#if 0
#define PUSH(s) \
        yy_push_state(s); \
        generateNewLine(); \
        generate_normal("<!-- PUSH  " #s " -->"); \
        generateNewLine();
        
#define POP(s) \
        yy_pop_state(); \
        generateNewLine(); \
        generate_normal("<!-- POP   " #s " -->"); \
        generateNewLine();
#else
    #define PUSH(s) yy_push_state(s);
    #define POP(s) yy_pop_state();
#endif
    
#define TRIMNORMAL(n)\
            do{ if(yyleng > n){\
                    yytext[yyleng - n]= '\0';\
                    generate_normal(yytext);\
                }}while(0)
%}

%option stack nomain yylineno noyywrap nounput
%option prefix="flex_scanner_"

%x verbatim_code options name_def sc_decl in_string sect2 pattern
%x comment sect2prolog start_cond sect3

NL	        \r?\n
OPTWS		[[:blank:]]*
WS          [[:blank:]]
NOT_WS		[^[:blank:]\r\n]
NAME        [[:alpha:]_][[:alnum:]_-]*
LEXOPT		[aceknopr]
REGEXOP     [\*\.\+\?\/\^\(\|\)\]\[]
NUMESCSEQ	\\(([0-7]{1,3})|x([[:xdigit:]]{1,2}))
CCL1        alnum|alpha|ascii|blank|cntrl|digit|graph
CCL2        lower|print|punct|space|upper|xdigit
CCL         {CCL1}|{CCL2}

%%
    int bracelevel=0;

<INITIAL>{
    ^"%{"           generatePreProc(yytext); PUSH(verbatim_code);
    ^"%"[sx]        generatePreProc(yytext); PUSH(sc_decl);
    ^"%option"      generatePreProc(yytext); PUSH(options);
    ^"%array"    |
    ^"%pointer"  |
    ^"%"{LEXOPT}    generatePreProc(yytext);
    ^{NAME}         generateFunction(yytext); PUSH(name_def);
    ^"%%"           generatePreProc(yytext); BEGIN(sect2);
    "/*"            startComment(yytext); PUSH(comment);
    {NL}            generateNewLine();
    [^\n_[:alpha:]%\/]+     generate_normal(yytext);
    .               generate_normal(yytext);
}
<verbatim_code>{
    ^"%}"           generatePreProc(yytext); POP(verbatim_code);
    [^\r\n%]+       generate_normal(yytext);
    [%\r]           generate_normal(yytext);
    {NL}            generateNewLine();
}
<options>{
    {WS}+           generate_normal(yytext);
    {NAME}          generateKeyWord(yytext);
    "="             generateSymbol(yytext);
    \"[^\"\n]*\"     {
                        startString("\"");
                        if(yyleng> 2){
                            yytext[yyleng-1] = '\0';
                            generateString(yytext+1);
                        }
                        endString("\"");
                    }
    {NL}            generateNewLine(); POP(options);
    .               generate_normal(yytext);
}
<sc_decl>{    
    {WS}+           generate_normal(yytext);
    {NAME}          generateFunction(yytext);
    {NL}            generateNewLine(); POP(sc_decl);
    .               generate_normal(yytext);
}

<name_def>{
    {WS}+           generate_normal(yytext);
    {NL}            generateNewLine(); yy_set_bol(1);POP(name_def);
    .               yyless(0); PUSH(pattern);
}
<pattern>{
    {WS}+           generate_normal(yytext); POP(pattern);
    {NL}            {
                        yy_set_bol(1);
                        yyless(0);
                        POP(pattern);
                    }
    "{"{NAME}"}"    {
                        generateSymbol("{");
                        yytext[yyleng-1] = '\0';
                        generateFunction(yytext+1);
                        generateSymbol("}");
                    }
    "\""            startString(yytext); PUSH(in_string);
    {REGEXOP}       generateSymbol(yytext);
    "<<EOF>>"       generateKeyWord(yytext);
    "[:"({CCL})":]"   {
                        generateSymbol("[:");
                        yytext[yyleng-2] = '\0';
                        generateKeyWord(yytext+2);
                        generateSymbol(":]");
                    }
    {NUMESCSEQ}     generateNumber(yytext);
    \\[^\n]         generatePreProc(yytext);
    .               generate_normal(yytext);
}
<in_string>{
    "\""            endString(yytext); POP(in_string);
    {NUMESCSEQ}     generateNumber(yytext);
    \\[^\n]         generatePreProc(yytext);
    {NL}            generateNewLine(); POP(in_string); /* actually an error */
    .               generateString(yytext);
}
<comment>{
    "*/"            endComment(yytext); POP(comment);
    [^*\n]+         generateComment(yytext);
    "*"             generateComment(yytext);
    {NL}            generateNewLine();
}
<sect2prolog>{
	^"%{".*	        ++bracelevel; generatePreProc(yytext);
	^"%}".*	        --bracelevel; generatePreProc(yytext);
	^{WS}.+         generate_normal(yytext);

	^{NOT_WS}.*	    {
                        if ( bracelevel <= 0 ) {
                            yyless( 0 );
                            yy_set_bol( 1 );
                            BEGIN(sect2);
                        }
                        else
                            generate_normal(yytext);
                    }

    {NL}            generateNewLine();
    .+              generate_normal(yytext);
}
<sect2>{
    "<"             generatePreProc(yytext); PUSH(start_cond);
	"/*"	        startComment(yytext); PUSH(comment);
	{WS}+		    generate_normal(yytext);
	^"%%"           generatePreProc(yytext); BEGIN(sect3);
	{NL}            generateNewLine();
    \}              generate_normal(yytext);
    .               yyless(0); PUSH(pattern);
}
<start_cond>{
    ">"             generatePreProc(yytext); POP(start_cond);
    ","             generate_normal(yytext);
    {NAME}|"*"      generateFunction(yytext);
    {NL}            generateNewLine();
    [^[:alpha:]_\n,>\*]+      generate_normal(yytext);
}
<sect3>{
    {NL}            generateNewLine();
    .+              generate_normal(yytext);
}
%%


/* vim:set ft=flex expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
