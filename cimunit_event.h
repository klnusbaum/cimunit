/**
 * Copyright 2011 Kurtis L. Nusbaum
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

#ifdef CIMUNIT_EVENT_H
#define CIMUNIT_EVENT_H
#include "cimunit_mutex.h"
typedef struct{
  const char *event_name;
  cimunit_mutex event_lock; 
} cimunit_event;

int cimunit_init_event(cimunit_event* to_init, const char *name);
int cimunit_destroy_event(cimunit_event* to_destroy);
#endif // CIMUNIT_EVENT_H
