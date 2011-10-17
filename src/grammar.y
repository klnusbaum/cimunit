%{
#include <stdio.h>
#include <string.h>

#include "cimunit_event_list.h"

void yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
	return 1;
}

cimunit_event_list_t *g_grammar_event_list = NULL;
cimunit_event_list_t *g_grammar_condition_list = NULL;

main()
{
    cimunit_event_list_init(&g_grammar_event_list);
    cimunit_event_list_init(&g_grammar_condition_list);
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
        cimunit_event_t *action_event =
          cimunit_event_list_find(g_grammar_condition_list, $3);
        
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
        
        if (!cimunit_event_list_find(g_grammar_event_list, $1)) {
            printf("Create event %s\n", $1);
            cimunit_event_t *new_event = cimunit_event_init($1);
            cimunit_event_list_add(&g_grammar_event_list, new_event);
        } else {
            printf("Found event %s\n", $1);
        }
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
        if (!cimunit_event_list_find(g_grammar_event_list, $1)) {
            cimunit_event_t *condition_event =
              cimunit_event_list_find(g_grammar_event_list, $1);
            if (condition_event) {
                printf("Add event %s to condition list\n", $1);
                cimunit_event_t *found_event = cimunit_event_init($1);
                cimunit_event_list_add(&g_grammar_event_list, found_event);
            }
        }
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
