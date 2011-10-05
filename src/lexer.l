%{
#include <stdio.h>
#include <string.h>
#include "bison_grammar.h"
%}

/* %option reentrant */

%%
[ \t]+                  /* ignore whitespace */;

\n              return SYMBOL_EOL;
,               return SYMBOL_COMMA;
->              return SYMBOL_IMPLIES;
\(              return SYMBOL_LPAREN;
\)              return SYMBOL_RPAREN;
&&              return SYMBOL_AND;
\|\|            return SYMBOL_OR;
\[              return SYMBOL_LBRACKET;
\]              return SYMBOL_RBRACKET;

[a-z0-9]+		yylval.string=strdup(yytext);return EVENT_NAME;

%%
