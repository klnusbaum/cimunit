/**
 * \file barrier_test.c
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
 
#include <stdio.h>

#include "cimunit_barrier.h"

cimunit_barrier_t my_barrier;
int count = 0;


void *bwait(void *value) {
    cimunit_barrier_wait(&my_barrier);
    //printf("Wait thread\n", ((long int)value));
    pthread_exit(NULL);
}



int main() {
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_attr_t attr;
    
    cimunit_barrier_init(&my_barrier);
        
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&thread1, &attr, bwait, (void *)1);
    pthread_create(&thread2, &attr, bwait, (void *)2);
    pthread_create(&thread3, &attr, bwait, (void *)3);

    //printf("Ready to signal\n");
    cimunit_barrier_unlock(&my_barrier);
    //printf("Signaled\n");
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    //printf("Done\n");

    pthread_attr_destroy(&attr);
    
    cimunit_barrier_destroy(&my_barrier);
    pthread_exit(NULL);
    
    return 0;
}
