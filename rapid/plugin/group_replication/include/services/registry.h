/* Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA */

#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>

#include <mysql/service_plugin_registry.h>
#include <mysql/components/services/registry.h>

/**
  This is the interface for the registrty module. This is a convenience
  class to conduct operations on the service registry. It can be used for
  instance to cache relevant and frequently used references to service
  implementations.
 */
class Registry_module_interface
{
public:

  /** The name of the membership service. */
  static const std::string SVC_NAME_MEMBERSHIP;
  /** The name of the member status service. */
  static const std::string SVC_NAME_STATUS;
  /** The name of the registry query service. */
  static const std::string SVC_NAME_REGISTRY_QUERY;

public:

  virtual ~Registry_module_interface() {}

  /**
    Initializes the registry handles. It acquires registry handles
    and allocates required memory.

    @return true if there was an error, false otherwise.
   */
  virtual bool initialize()= 0;

  /**
    SHALL release the registry handles and frees memory that
    may have been in use. Clean up.

    @return true if there was an error, false otherwise.
   */
  virtual bool finalize()= 0;

  /**
    SHALL return the service registry handle if initialized already.

    @return the service registry handle if initialized. NULL otherwise.
   */
  virtual SERVICE_TYPE(registry) *get_registry_handle()= 0;

  /**
    SHALL return the service registry query handle if initialized already.

    @return the service registry query handle if initialized. NULL otherwise.
   */
  virtual SERVICE_TYPE(registry_query) *get_registry_query_handle()= 0;
};

/**
  This is the implementation of the registry module interface.

  This implementation will acquire a reference to the service registry
  and to the registry query service when initialized. It will only release
  these references when the module is finalized.
 */
class Registry_module : public Registry_module_interface
{
private:

  /**
    Cached reference to the service registry.
   */
  SERVICE_TYPE(registry) *m_registry;

  /**
    Cached reference to the registry query service.
   */
  SERVICE_TYPE(registry_query) *m_registry_query;

  /* Disable copy and assignment constructors. */
  Registry_module(const Registry_module& rhs);
  Registry_module& operator=(const Registry_module rhs);

public:
  Registry_module() :
    m_registry(NULL),
    m_registry_query(NULL)
  {}

  virtual ~Registry_module() { finalize(); }

  bool initialize();
  bool finalize();
  SERVICE_TYPE(registry) *get_registry_handle();
  SERVICE_TYPE(registry_query) *get_registry_query_handle();
};

#endif