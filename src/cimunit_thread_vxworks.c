/**
 * \file cimunit_thread_vxworks.c
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

#include "cimunit_thread.h"

#include <vxWorks.h>
#include <sysLib.h>
#include <taskLib.h>
#include <private/taskLibP.h>

static int vxworks_task_handoff(int function, int arg1) {
  cimunit_task_entry_t func = (cimunit_task_entry_t)function;
  (func)((void *)arg1);
  return 0;
}


int cimunit_thread_create(
  cimunit_thread_t * RESTRICT thread, 
  cimunit_task_entry_t function,
  void *RESTRICT arg)
{
  *thread = taskSpawn(NULL, 100, 0, 16332, vxworks_task_handoff,
                      (int)function, (int)arg,
                      0, 0, 0, 0, 0, 0, 0, 0);
  return 0;
}

int cimunit_thread_join(cimunit_thread_t thread, void **value_ptr){
  TASK_DESC taskInfo;
  while(OK == taskInfoGet(thread, &taskInfo)) {
    if (WIND_DEAD == taskInfo.td_status) {
      break;
    }
    taskDelay(1);
  }
  return 0;
}

cimunit_thread_t cimunit_thread_self(){
  return taskIdSelf();
}

void cimunit_thread_sleep(int time) {
  int clkRate = sysClkRateGet();

  taskDelay(((time * sysClkRateGet()) / 1000) + 1);
}

