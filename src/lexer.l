%{
#include <stdio.h>
#include <string.h>
#include "bison_grammar.h"
%}

%%
[0-9]+                  yylval.number=atoi(yytext); return NUMBER;
heater			return TOKHEATER;
heat                    return TOKHEAT;
on|off                  yylval.number=!strcmp(yytext,"on"); return STATE;
target                  return TOKTARGET;
temperature             return TOKTEMPERATURE;
\n                      /* ignore end of line */;
[ \t]+                  /* ignore whitespace */;

,               printf("Comma\n");return COMMA;
->              printf("Implies\n");return IMPLIES;

[a-z0-9]+		yylval.string=strdup(yytext);return EVENT_NAME;

%%
