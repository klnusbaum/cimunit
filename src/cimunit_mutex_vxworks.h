/**
 * \file cimunit_mutex_vxworks.h
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

#ifndef CIMUNIT_MUTEX_VXWORKS_H
#define CIMUNIT_MUTEX_VXWORKS_H

#include <vxWorks.h>
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif
  
/// \addtogroup cimunit_mutex cimunit_mutex Module
/// @{

/// Concrete type for mutex under VxWorks
typedef SEM_ID cimunit_mutex_t;

/// Concrete type for mutex attribute under VxWorks
typedef int cimunit_mutex_attr_t;

/// @}

#ifdef __cplusplus
}
#endif
  
#endif // CIMUNIT_MUTEX_VXWORKS_H

