/*
  Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef SERVICE_LOCKING_INCLUDED
#define SERVICE_LOCKING_INCLUDED

/**
  @file include/mysql/service_locking.h

  Implements ::mysql_locking_service_st
*/

#ifdef __cplusplus
class THD;
#define MYSQL_THD THD*
#else
#define MYSQL_THD void*
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
  Types of locking service locks.
  LOCKING_SERVICE_READ is compatible with LOCKING_SERVICE_READ.
  All other combinations are incompatible.
*/
enum enum_locking_service_lock_type
{ LOCKING_SERVICE_READ, LOCKING_SERVICE_WRITE };

typedef int (*mysql_acquire_locks_t)(MYSQL_THD opaque_thd,
                                     const char* lock_namespace,
                                     const char**lock_names,
                                     size_t lock_num,
                                     enum enum_locking_service_lock_type lock_type,
                                     unsigned long lock_timeout);

typedef int (*mysql_release_locks_t)(MYSQL_THD opaque_thd,
                                     const char* lock_namespace);

/**
  @ingroup group_ext_plugin_services

  This service provides support for taking read/write locks.
  It is intended for use with fabric, but it is still a general
  service. The locks are in a separate namespace from other
  locks in the server, and there is also no interactions with
  transactions (i.e. locks are not released on commit/abort).

  These locks are implemented using the metadata lock (MDL) subsystem
  and thus deadlocks involving locking service locks and other types
  of metadata will be detected using the MDL deadlock detector.
*/
extern struct mysql_locking_service_st {
  /**
    Acquire locking service locks.

    @param opaque_thd      Thread handle. If NULL, current_thd will be used.
    @param lock_namespace  Namespace of the locks to acquire.
    @param lock_names      Array of names of the locks to acquire.
    @param lock_num        Number of elements in 'lock_names'.
    @param lock_type       Lock type to acquire. LOCKING_SERVICE_READ or _WRITE.
    @param lock_timeout    Number of seconds to wait before giving up.

    @retval 1              Acquisition failed, error has been reported.
    @retval 0              Acquisition successful, all locks acquired.

    @note both lock_namespace and lock_names are limited to 64 characters max.
    Names are compared using binary comparison.

    @sa acquire_locking_service_locks, MDL_context::acquire_locks
  */
  mysql_acquire_locks_t mysql_acquire_locks;
  /**
    Release all lock service locks taken by the given connection
    in the given namespace.

    @param opaque_thd      Thread handle. If NULL, current_thd will be used.
    @param lock_namespace  Namespace of the locks to release.

    @retval 1              Release failed, error has been reported.
    @retval 0              Release successful, all locks acquired.

    @sa release_locking_service_locks, MDL_context::release_locks
  */
  mysql_release_locks_t mysql_release_locks;
} *mysql_locking_service;

#ifdef MYSQL_DYNAMIC_PLUGIN

#define mysql_acquire_locking_service_locks(_THD, _NAMESPACE, _NAMES, _NUM, \
                                            _TYPE, _TIMEOUT)            \
  mysql_locking_service->mysql_acquire_locks(_THD, _NAMESPACE, _NAMES, _NUM, \
                                             _TYPE, _TIMEOUT)
#define mysql_release_locking_service_locks(_THD, _NAMESPACE) \
  mysql_locking_service->mysql_release_locks(_THD, _NAMESPACE)

#else

int mysql_acquire_locking_service_locks(MYSQL_THD opaque_thd,
                                        const char* lock_namespace,
                                        const char**lock_names,
                                        size_t lock_num,
                                        enum enum_locking_service_lock_type lock_type,
                                        unsigned long lock_timeout);

int mysql_release_locking_service_locks(MYSQL_THD opaque_thd,
                                        const char* lock_namespace);

#endif /* MYSQL_DYNAMIC_PLUGIN */

#ifdef __cplusplus
}
#endif

#endif /* SERVICE_LOCKING_INCLUDED */
