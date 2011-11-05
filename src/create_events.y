/**
 * \file create_events.y
 *
 * Copyright 2011 Dale Frampton
 * 
 * This file is part of cimunit.
 * 
 * cimunit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * cimunit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cimunit.  If not, see <http://www.gnu.org/licenses/>.
 */
 
%{
#include <stdio.h>
#include <string.h>

#include "cimunit_event_list.h"
#include "cimunit_schedule.h"


// Defines

extern int create_events_parse(cimunit_event_list_t **event_list); // From create_events.y
extern void create_events__scan_string(char *string); // From create_events.l
extern int create_events_lex (void); // From create_events.l


/// Display errors to the terminal
///
/// \param event_list - event list passed to the parser
/// \param str - error string
void create_events_error(struct cimunit_event_list **event_list, const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}


/// Indicate there is no more input after the EOF.
int create_events_wrap()
{
	return 1;
}


/// Build a schedule
///
/// \return the completed schedule
cimunit_schedule_t *cimunit_schedule_parse(char *schedule_string) {
    cimunit_schedule_t *schedule = cimunit_schedule_init();
    
    schedule->schedule_string = malloc(strlen(schedule_string) + 1);
    strcpy(schedule->schedule_string, schedule_string);
    //schedule->schedule_string = strdup(schedule_string);
    
    // Parse the schedule string into the schedule object.
    create_events__scan_string(schedule_string);
    create_events_parse(&schedule->event_list);
    
    return schedule;
}

%}

%token SYMBOL_COMMA SYMBOL_IMPLIES SYMBOL_EOL SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_AND
       SYMBOL_OR SYMBOL_LBRACKET SYMBOL_RBRACKET

%union 
{
	const char *string;
	struct cimunit_event_list *conditionList;
	struct cimunit_event *event;
}

%name-prefix "create_events_"

%parse-param {struct cimunit_event_list **event_list}

%token <string> EVENT_NAME

%type <string> blockEvent
%type <conditionList> condition basicCondition
%type <event> basicEvent

%start schedules

%%

schedules:
    | schedule
    | schedules SYMBOL_COMMA schedule

schedule:
    ordering

ordering:
    condition SYMBOL_IMPLIES basicEvent
    {
        cimunit_event_list_t *condition = $1;
        cimunit_event_t *action_event = $3;
        
        while(condition != NULL) {
            cimunit_event_add_action(condition->event, action_event);
            condition = condition->next;
        }
        
        cimunit_event_list_destroy(&$1);
    }
    ;

basicEvent:
    EVENT_NAME
    {
        cimunit_event_t *event = cimunit_event_list_find(*event_list, $1);
        
        if (!event) {
            event = (cimunit_event_t*)malloc(sizeof(cimunit_event_t));
            cimunit_event_init(event, $1);
            cimunit_event_list_add(event_list, event);
        }
        
        $$ = event;
    }
    ;

blockEvent:
    SYMBOL_LBRACKET basicEvent SYMBOL_RBRACKET
    {
        $$ = $2->event_name;
    }
    ;

basicCondition:
    basicEvent
    {
        cimunit_event_t *condition_event = $1;

        if (condition_event) {
            cimunit_event_list_t *new_condition = cimunit_event_list_init();
            cimunit_event_list_add(&new_condition, condition_event);
            $$ = new_condition;
        }
    }
    | blockEvent
    {
        $$ = NULL;
        yyerror(event_list, "Blocking events are not supported");
        YYERROR;
    }

condition:
    basicCondition
    {
        $$ = $1;
    }
    | condition SYMBOL_OR basicCondition
    {
        cimunit_event_list_t *lhs = $1;
        cimunit_event_list_t *rhs = $3;
        cimunit_event_list_union(&lhs, rhs);
        cimunit_event_list_destroy(&rhs);
        $$ = lhs;
    }
    | condition SYMBOL_AND basicCondition
    {
        cimunit_event_list_t *lhs = $1;
        cimunit_event_list_t *rhs = $3;
        cimunit_event_list_union(&lhs, rhs);
        cimunit_event_list_destroy(&rhs);
        $$ = lhs;
    }
    | SYMBOL_LPAREN condition SYMBOL_RPAREN
    {
        $$ = $2;
    }
    ;
