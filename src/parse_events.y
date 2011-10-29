/**
 * \file parse_events.y
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

extern int parse_events_parse(cimunit_event_list_t **event_list,
                              char *action_event); // From parse_events.y
extern void parse_events__scan_string(char *string); // From parse_events.l
extern int parse_events_lex (void); // From parse_events.l


/// Display errors to the terminal
///
/// \param event_list - event list passed to the parser
/// \param str - error string
void parse_events_error(struct cimunit_event_list **event_list,
                        const char *action_event, const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}


/// Indicate there is no more input after the EOF.
int parse_events_wrap()
{
	return 1;
}


/// Build a schedule
///
/// \return the completed schedule
bool cimunit_parse_schedule_runtime(cimunit_schedule_t *schedule,
                                    char *action_event) {
    // Parse the schedule string to determine if the action event is unblocked
    parse_events__scan_string(schedule->schedule_string);
    parse_events_parse(&schedule->event_list, action_event);
    
    return false;
}

%}

%token SYMBOL_COMMA SYMBOL_IMPLIES SYMBOL_EOL SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_AND
       SYMBOL_OR SYMBOL_LBRACKET SYMBOL_RBRACKET

%union 
{
	char *string;
}

%name-prefix "parse_events_"

%parse-param {struct cimunit_event_list **event_list}
%parse-param {char *action_event}

%token <number> STATE
%token <number> NUMBER
%token <string> EVENT_NAME

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
    }
    ;

basicEvent:
    EVENT_NAME
    {
    }
    ;

blockEvent:
    SYMBOL_LBRACKET basicEvent SYMBOL_RBRACKET
    {
    }
    ;

basicCondition:
    basicEvent
    {
    }
    | blockEvent
    {
        yyerror(event_list, action_event, "Blocking events are not supported");
        YYERROR;
    }

condition:
    basicCondition
    {
    }
    | condition SYMBOL_OR basicCondition
    {

    }
    | condition SYMBOL_AND basicCondition
    {
    }
    | SYMBOL_LPAREN condition SYMBOL_RPAREN
    {
    }
    ;
