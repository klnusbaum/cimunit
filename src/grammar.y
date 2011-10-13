%{
#include <stdio.h>
#include <string.h>

void yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
	return 1;
}

main()
{
	yyparse();
}

char *heater="default";

%}

%token SYMBOL_COMMA SYMBOL_IMPLIES SYMBOL_EOL SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_AND
       SYMBOL_OR SYMBOL_LBRACKET SYMBOL_RBRACKET

%union 
{
	int number;
	char *string;
}

/* %define api.pure */

%token <number> STATE
%token <number> NUMBER
%token <string> EVENT_NAME

%type <string> basicEvent blockEvent basicCondition

%start schedules

%%

schedules:
    | schedules schedule SYMBOL_EOL
    | schedules schedule SYMBOL_COMMA

schedule:
    ordering

ordering:
    condition SYMBOL_IMPLIES basicEvent
    ;

basicEvent:
    EVENT_NAME
    {
        $$ = $1;
    }
    ;

blockEvent:
    SYMBOL_LBRACKET basicEvent SYMBOL_RBRACKET
    {
        $$ = $2;
    }
    ;

basicCondition:
    basicEvent
    {
        $$ = $1;
    }
    | blockEvent
    {
        $$ = $1;
    }

condition:
    | basicCondition
    | condition SYMBOL_OR basicCondition
    | condition SYMBOL_AND basicCondition
    | SYMBOL_LPAREN condition SYMBOL_RPAREN
    ;
