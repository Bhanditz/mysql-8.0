/* Copyright (c) 2008, 2017, Oracle and/or its affiliates. All rights reserved.

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

/**
  @file storage/perfschema/table_session_account_connect_attrs.cc
  TABLE SESSION_ACCOUNT_CONNECT_ATTRS.
*/

#include "storage/perfschema/table_session_account_connect_attrs.h"

#include <sys/types.h>

#include "my_dbug.h"

THR_LOCK table_session_account_connect_attrs::m_table_lock;

Plugin_table table_session_account_connect_attrs::m_table_def(
  /* Schema name */
  "performance_schema",
  /* Name */
  "session_account_connect_attrs",
  /* Definition */
  "  PROCESSLIST_ID INT NOT NULL,\n"
  "  ATTR_NAME VARCHAR(32) NOT NULL,\n"
  "  ATTR_VALUE VARCHAR(1024),\n"
  "  ORDINAL_POSITION INT,\n"
  "  PRIMARY KEY (PROCESSLIST_ID, ATTR_NAME)\n",
  /* Options */
  " ENGINE=PERFORMANCE_SCHEMA CHARACTER SET utf8 COLLATE utf8_bin",
  /* Tablespace */
  nullptr);

PFS_engine_table_share table_session_account_connect_attrs::m_share = {
  &pfs_readonly_world_acl,
  table_session_account_connect_attrs::create,
  NULL, /* write_row */
  NULL, /* delete_all_rows */
  cursor_by_thread_connect_attr::get_row_count,
  sizeof(pos_connect_attr_by_thread_by_attr), /* ref length */
  &m_table_lock,
  &m_table_def,
  false /* perpetual */
};

PFS_engine_table *
table_session_account_connect_attrs::create(PFS_engine_table_share *)
{
  return new table_session_account_connect_attrs();
}

table_session_account_connect_attrs::table_session_account_connect_attrs()
  : table_session_connect(&m_share)
{
}

bool
table_session_account_connect_attrs::thread_fits(PFS_thread *thread)
{
  PFS_thread *current_thread = PFS_thread::get_current_thread();
  /* The current thread may not have instrumentation attached. */
  if (current_thread == NULL)
  {
    return false;
  }

  /* The thread we compare to, by definition, has some instrumentation. */
  DBUG_ASSERT(thread != NULL);

  uint username_length = current_thread->m_username_length;
  uint hostname_length = current_thread->m_hostname_length;

  if ((thread->m_username_length != username_length) ||
      (thread->m_hostname_length != hostname_length))
  {
    return false;
  }

  if (memcmp(thread->m_username, current_thread->m_username, username_length) !=
      0)
  {
    return false;
  }

  if (memcmp(thread->m_hostname, current_thread->m_hostname, hostname_length) !=
      0)
  {
    return false;
  }

  return true;
}
