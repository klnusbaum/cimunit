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

%token TOKHEATER TOKHEAT TOKTARGET TOKTEMPERATURE COMMA IMPLIES

%union 
{
	int number;
	char *string;
}

%token <number> STATE
%token <number> NUMBER
%token <string> EVENT_NAME

%type <string> basicEvent condition action


%%

commands:
	| schedules
	;


command:
	heat_switch | target_set | heater_select

heat_switch:
	TOKHEAT STATE 
	{
		if($2)
			printf("\tHeater '%s' turned on\n", heater);
		else
			printf("\tHeat '%s' turned off\n", heater);
	}
	;

target_set:
	TOKTARGET TOKTEMPERATURE NUMBER
	{
		printf("\tHeater '%s' temperature set to %d\n",heater, $3);
	}
	;

heater_select:
	TOKHEATER EVENT_NAME
	{
		printf("\tSelected heater '%s'\n",$2);
		heater=$2;
	}
	;
	

schedules:
    | schedules ordering COMMA
    ;

basicEvent:
    EVENT_NAME
    {
        $$ = $1;
    }
    ;
    
    
condition:
    basicEvent
    {
        $$ = $1;
    }
    ;
    
action:
    basicEvent
    {
        $$ = $1;
    }
    ;
    
ordering:
    condition IMPLIES action
    {
        printf("Ordering: %s -> %s\n", $1, $3);
    }
    ;

