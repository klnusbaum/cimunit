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
    {
        printf("Get action event '%s'\n", $3);
        printf("For each item in condition event list\n");
        printf("\tRegister action event's barrier with condition event\n");
        printf("Clear condition event list\n");
    }
    ;

basicEvent:
    EVENT_NAME
    {
        $$ = $1;
        printf("Does event '%s' already exit?\n", $1);
        printf("If not, create event '%s'\n", $1);
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
        yyerror("Blocking events are not supported");
        YYERROR;
    }

condition:
    basicCondition
    {
        printf("Add event '%s' to condition event list\n", $1);
    }
    | condition SYMBOL_OR basicCondition
    {
        printf("Add event '%s' to condition event list\n", $3);
    }
    | condition SYMBOL_AND basicCondition
    {
        printf("Add event '%s' to condition event list\n", $3);
    }
    | SYMBOL_LPAREN condition SYMBOL_RPAREN
    ;
