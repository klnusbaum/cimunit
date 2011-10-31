/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2004  Anil Kumar, Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
void print_example_results(void)
{
  fprintf(stdout, "\n\nExpected Test Results:"
                  "\n\n  Error Handling  Type      # Run   # Pass   # Fail"
                  "\n\n  ignore errors   suites%9u%9u%9u"
                    "\n                  tests %9u%9u%9u"
                    "\n                  asserts%8u%9u%9u"
                  "\n\n  stop on error   suites%9u%9u%9u"
                    "\n                  tests %9u%9u%9u"
                    "\n                  asserts%8u%9u%9u\n\n",
                  14, 14, 3,
                  31, 10, 21,
                  89, 47, 42,
                  4, 4, 1,
                  12, 9, 3,
                  12, 9, 3);
}

