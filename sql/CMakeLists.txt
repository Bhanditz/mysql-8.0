# Copyright (c) 2006, 2017 Oracle and/or its affiliates. All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA


INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/include 
  ${CMAKE_SOURCE_DIR}/sql/conn_handler
  ${CMAKE_SOURCE_DIR}/libbinlogevents/include
  ${CMAKE_SOURCE_DIR}/sql 
  ${CMAKE_SOURCE_DIR}/sql/auth
  ${CMAKE_SOURCE_DIR}/extra/regex
  ${ZLIB_INCLUDE_DIR}
  ${SSL_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/sql
  ${LZ4_INCLUDE_DIR}
)

SET(CONF_SOURCES
  ${CMAKE_CURRENT_BINARY_DIR}/sql_builtin.cc 
)
SET(GEN_SOURCES
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.h 
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.h 
  ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.cc
  ${CMAKE_CURRENT_BINARY_DIR}/lex_hash.h 
)
SET(GEN_DIGEST_SOURCES
  ${CMAKE_CURRENT_BINARY_DIR}/lex_token.h 
)

SET_SOURCE_FILES_PROPERTIES(${GEN_SOURCES}
                            ${GEN_DIGEST_SOURCES}
                            ${CONF_SOURCES}
                            PROPERTIES GENERATED 1)

# Gen_lex_token
# Make sure sql_yacc.h is generated before compiling gen_lex_token
ADD_EXECUTABLE(gen_lex_token gen_lex_token.cc)
ADD_DEPENDENCIES(gen_lex_token GenServerSource)

ADD_CUSTOM_COMMAND(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lex_token.h
  COMMAND gen_lex_token > lex_token.h
  DEPENDS gen_lex_token
)

ADD_DEFINITIONS(-DMYSQL_SERVER)
IF(SSL_DEFINES)
 ADD_DEFINITIONS(${SSL_DEFINES})
ENDIF()

SET(DD_SOURCES
  dd/collection.cc
  dd/dd_event.cc
  dd/dd_routine.cc
  dd/dd_schema.cc
  dd/dd_table.cc
  dd/dd_tablespace.cc
  dd/dd_trigger.cc
  dd/dd_view.cc

  dd/impl/bootstrapper.cc
  dd/impl/dd.cc
  dd/impl/dictionary_impl.cc
  dd/impl/properties_impl.cc
  dd/impl/system_registry.cc
  dd/impl/transaction_impl.cc
  dd/impl/utils.cc
  dd/impl/sdi.cc
  dd/impl/sdi_api.cc
  dd/impl/sdi_file.cc
  dd/impl/sdi_tablespace.cc
  dd/impl/string_type.cc

  dd/impl/cache/dictionary_client.cc
  dd/impl/cache/local_multi_map.cc
  dd/impl/cache/multi_map_base.cc
  dd/impl/cache/shared_multi_map.cc
  dd/impl/cache/shared_dictionary_cache.cc
  dd/impl/cache/storage_adapter.cc

  dd/impl/raw/object_keys.cc
  dd/impl/raw/raw_record.cc
  dd/impl/raw/raw_record_set.cc
  dd/impl/raw/raw_table.cc

  dd/impl/system_views/character_sets.cc
  dd/impl/system_views/collations.cc
  dd/impl/system_views/collation_charset_applicability.cc
  dd/impl/system_views/columns.cc
  dd/impl/system_views/column_statistics.cc
  dd/impl/system_views/events.cc
  dd/impl/system_views/key_column_usage.cc
  dd/impl/system_views/parameters.cc
  dd/impl/system_views/routines.cc
  dd/impl/system_views/schemata.cc
  dd/impl/system_views/statistics.cc
  dd/impl/system_views/st_spatial_reference_systems.cc
  dd/impl/system_views/st_geometry_columns.cc
  dd/impl/system_views/tables.cc
  dd/impl/system_views/table_constraints.cc
  dd/impl/system_views/triggers.cc
  dd/impl/system_views/views.cc

  dd/impl/tables/table_stats.cc
  dd/impl/tables/index_stats.cc
  dd/impl/tables/character_sets.cc
  dd/impl/tables/collations.cc
  dd/impl/tables/columns.cc
  dd/impl/tables/column_statistics.cc
  dd/impl/tables/column_type_elements.cc
  dd/impl/tables/dd_properties.cc
  dd/impl/tables/events.cc
  dd/impl/tables/foreign_key_column_usage.cc
  dd/impl/tables/foreign_keys.cc
  dd/impl/tables/index_column_usage.cc
  dd/impl/tables/indexes.cc
  dd/impl/tables/index_partitions.cc
  dd/impl/tables/parameters.cc
  dd/impl/tables/parameter_type_elements.cc
  dd/impl/tables/routines.cc
  dd/impl/tables/schemata.cc
  dd/impl/tables/spatial_reference_systems.cc
  dd/impl/tables/table_partitions.cc
  dd/impl/tables/table_partition_values.cc
  dd/impl/tables/tables.cc
  dd/impl/tables/tablespace_files.cc
  dd/impl/tables/tablespaces.cc
  dd/impl/tables/triggers.cc
  dd/impl/tables/view_routine_usage.cc
  dd/impl/tables/view_table_usage.cc

  dd/impl/types/index_stat_impl.cc
  dd/impl/types/table_stat_impl.cc
  dd/impl/types/abstract_table_impl.cc
  dd/impl/types/charset_impl.cc
  dd/impl/types/collation_impl.cc
  dd/impl/types/column_impl.cc
  dd/impl/types/column_statistics_impl.cc
  dd/impl/types/column_type_element_impl.cc
  dd/impl/types/entity_object_table_impl.cc
  dd/impl/types/entity_object_impl.cc
  dd/impl/types/event_impl.cc
  dd/impl/types/foreign_key_element_impl.cc
  dd/impl/types/foreign_key_impl.cc
  dd/impl/types/function_impl.cc
  dd/impl/types/index_element_impl.cc
  dd/impl/types/index_impl.cc
  dd/impl/types/parameter_impl.cc
  dd/impl/types/parameter_type_element_impl.cc
  dd/impl/types/partition_impl.cc
  dd/impl/types/partition_index_impl.cc
  dd/impl/types/partition_value_impl.cc
  dd/impl/types/procedure_impl.cc
  dd/impl/types/routine_impl.cc
  dd/impl/types/schema_impl.cc
  dd/impl/types/spatial_reference_system_impl.cc
  dd/impl/types/table_impl.cc
  dd/impl/types/tablespace_file_impl.cc
  dd/impl/types/tablespace_impl.cc
  dd/impl/types/trigger_impl.cc
  dd/impl/types/view_impl.cc
  dd/impl/types/view_routine_impl.cc
  dd/impl/types/view_table_impl.cc
  dd/impl/types/weak_object_impl.cc

  dd/info_schema/metadata.cc
  dd/info_schema/show.cc
  dd/info_schema/show_query_builder.cc
  dd/info_schema/stats.cc

  dd/performance_schema/init.cc

  dd/upgrade/event.cc
  dd/upgrade/global.cc
  dd/upgrade/routine.cc
  dd/upgrade/schema.cc
  dd/upgrade/table.cc
  dd/upgrade/upgrade.cc
)

SET(SQL_GIS_SOURCES
  geometry_rtree.cc
  gis/covered_by.cc
  gis/crosses.cc
  gis/difference.cc
  gis/disjoint.cc
  gis/distance.cc
  gis/equals.cc
  gis/gc_utils.cc
  gis/geometries.cc
  gis/intersects.cc
  gis/mbr_utils.cc
  gis/overlaps.cc
  gis/ring_flip_visitor.cc
  gis/rtree_support.cc
  gis/srs/srs.cc
  gis/srs/wkt_parser.cc
  gis/touches.cc
  gis/union.cc
  gis/within.cc
  gis/wkb_parser.cc
  item_geofunc.cc
  item_geofunc_buffer.cc
  item_geofunc_internal.cc
  item_geofunc_relchecks.cc
  item_geofunc_relchecks_bgwrap.cc
  item_geofunc_setops.cc
)

SET(MYSQL_SERVER_SUB_COMPONENT_SOURCES
  server_component/mysql_string_service.cc
  server_component/persistent_dynamic_loader.cc
  )

SET(SQL_SHARED_SOURCES
  abstract_query_plan.cc
  auth/auth_common.cc
  auth/dynamic_privileges_impl.cc
  auth/dynamic_privilege_table.cc
  auth/sql_authentication.cc
  auth/sql_auth_cache.cc
  auth/sql_authorization.cc
  auth/sql_user_table.cc
  auth/sql_user.cc
  auth/password.c
  auth/password_policy_service.cc
  auth/sql_security_ctx.cc
  auth/service_security_context.cc
  auto_thd.cc
  keyring_service.cc
  auth/role_tables.cc
  ssl_wrapper_service.cc
  bootstrap.cc
  check_stack.cc
  conn_handler/connection_handler_manager.cc 
  current_thd.cc
  dd_sql_view.cc
  dd_sp.cc
  dd_table_share.cc
  debug_sync.cc
  default_values.cc
  derror.cc
  error_handler.cc
  field.cc
  field_conv.cc 
  filesort.cc
  filesort_utils.cc
  aggregate_check.cc
  gstream.cc
  handler.cc
  histograms/equi_height.cc
  histograms/equi_height_bucket.cc
  histograms/histogram.cc
  histograms/singleton.cc
  histograms/value_map.cc
  hostname.cc
  init.cc
  item.cc
  item_buff.cc
  item_cmpfunc.cc 
  item_create.cc
  item_func.cc
  item_json_func.cc
  item_row.cc 
  item_strfunc.cc
  item_subselect.cc
  item_sum.cc
  window.cc
  item_timefunc.cc 
  item_xmlfunc.cc 
  item_inetfunc.cc
  json_binary.cc
  json_diff.cc
  json_dom.cc
  json_path.cc
  key.cc
  key_spec.cc
  keycaches.cc
  lock.cc
  locking_service.cc
  log.cc
  mdl.cc
  my_decimal.cc
  mysqld.cc
  mysqld_thd_manager.cc
  opt_costconstantcache.cc
  opt_costconstants.cc
  opt_costmodel.cc
  opt_explain.cc
  opt_explain_format.cc
  opt_explain_traditional.cc
  opt_explain_json.cc
  opt_hints.cc
  opt_range.cc
  opt_statistics.cc
  opt_sum.cc 
  opt_trace.cc
  opt_trace2server.cc
  options_parser.cc
  parse_file.cc
  parse_tree_helpers.cc
  parse_tree_hints.cc
  parse_tree_items.cc
  parse_tree_node_base.cc
  parse_tree_nodes.cc
  parse_tree_partitions.cc
  select_lex_visitor.cc
  parser_service.cc
  partition_info.cc
  partitioning/partition_handler.cc
  persisted_variable.cc
  procedure.cc 
  protocol_classic.cc
  psi_memory_key.cc
  query_result.cc
  records.cc
  rpl_group_replication.cc
  rpl_handler.cc
  rpl_transaction_ctx.cc
  rpl_transaction_write_set_ctx.cc
  rpl_trx_tracking.cc
  rpl_write_set_handler.cc
  rules_table_service.cc
  rwlock_scoped_lock.cc
  sdi_utils.cc
  session_tracker.cc
  set_var.cc 
  sp.cc
  sp_cache.cc
  sp_head.cc
  sp_instr.cc
  sp_pcontext.cc 
  sp_rcontext.cc
  spatial.cc
  string_service.cc
  sql_admin.cc
  sql_alloc_error_handler.cc
  sql_alter.cc
  sql_alter_instance.cc
  sql_base.cc 
  sql_bootstrap.cc
  sql_initialize.cc
  sql_cache.cc
  sql_call.cc
  sql_class.cc
  sql_component.cc
  sql_cmd_ddl_table.cc
  sql_connect.cc
  sql_crypt.cc
  sql_cursor.cc
  sql_data_change.cc
  sql_db.cc
  sql_delete.cc
  sql_derived.cc
  sql_digest.cc
  sql_do.cc 
  sql_error.cc
  sql_exception_handler.cc
  sql_executor.cc
  sql_get_diagnostics.cc
  sql_handler.cc
  sql_help.cc
  sql_import.cc
  sql_insert.cc
  sql_join_buffer.cc
  sql_lex.cc 
  sql_lex_hash.cc
  sql_lex_hints.cc
  sql_list.cc
  sql_load.cc
  sql_locale.cc
  sql_manager.cc
  sql_optimizer.cc
  sql_parse.cc
  sql_partition.cc
  sql_partition_admin.cc
  sql_planner.cc
  sql_plugin.cc
  sql_prepare.cc
  sql_profile.cc
  sql_query_rewrite.cc
  sql_reload.cc
  sql_rename.cc
  sql_resolver.cc
  sql_rewrite.cc
  sql_select.cc
  sql_servers.cc
  sql_show.cc
  sql_show_status.cc
  sql_signal.cc
  sql_state.cc
  sql_table.cc
  sql_tablespace.cc
  sql_test.cc
  sql_thd_internal_api.cc
  sql_thd_api.cc
  sql_time.cc
  sql_timer.cc
  sql_tmp_table.cc
  sql_trigger.cc
  sql_truncate.cc
  sql_udf.cc
  sql_union.cc
  sql_update.cc
  sql_view.cc
  stateless_allocator.cc
  strfunc.cc
  sys_vars.cc
  sys_vars_resource_mgr.cc
  system_variables.cc
  table.cc
  table_cache.cc
  table_trigger_dispatcher.cc
  tc_log.cc
  thr_malloc.cc 
  transaction.cc
  transaction_info.cc
  trigger.cc
  trigger_creation_ctx.cc
  trigger_chain.cc
  tztime.cc
  uniques.cc
  xa.cc
  ${DD_SOURCES}
  ${MYSQL_SERVER_SUB_COMPONENT_SOURCES}
)

# Needed so that IDEs (e.g. Xcode) can see all sources when searching
FILE(GLOB_RECURSE SQL_HEADERS
  "${CMAKE_SOURCE_DIR}/include/*.h"
  "${CMAKE_SOURCE_DIR}/sql/*.h"
  "${CMAKE_SOURCE_DIR}/storage/*.h"
)

# Needed so that IDEs (e.g. Xcode) can see all sources when searching 
FILE(GLOB_RECURSE SQL_HEADERS
  "${CMAKE_SOURCE_DIR}/include/*.h"
  "${CMAKE_SOURCE_DIR}/sql/*.h"
  "${CMAKE_SOURCE_DIR}/storage/*.h"
) 

SET(SQL_SOURCE
  ${GEN_SOURCES}
  ${GEN_DIGEST_SOURCES}
  ${CONF_SOURCES}
  ${SQL_SHARED_SOURCES}
  ${SQL_HEADERS}
  ../extra/lz4/xxhash.c
  ../libmysql/errmsg.cc
  ../sql-common/client.cc
  ../sql-common/client_plugin.c
  ../sql-common/client_authentication.cc
  ../sql-common/net_serv.cc
  ../sql-common/sql_string.cc 
  command_service.cc
  conn_handler/channel_info.cc
  conn_handler/connection_handler_per_thread.cc
  conn_handler/connection_handler_one_thread.cc
  conn_handler/socket_connection.cc
  conn_handler/init_net_server_extension.cc
  des_key_file.cc
  event_data_objects.cc
  event_db_repository.cc 
  event_parse_data.cc
  event_queue.cc
  event_scheduler.cc
  events.cc
  mf_iocache.cc
  protocol_callback.cc
  signal_handler.cc
  sql_audit.cc
  sql_client.cc
  srv_session.cc
  srv_session_info_service.cc
  srv_session_service.cc
  )

IF(NOT WIN32)
  LIST(APPEND SQL_SOURCE mysqld_daemon.cc)
ENDIF()

IF(WIN32)
  LIST(APPEND SQL_SOURCE
              named_pipe.cc
              conn_handler/named_pipe_connection.cc
              conn_handler/shared_memory_connection.cc
      )
ENDIF()

# Source files that use Boost
SET(SQL_BOOST_SOURCES
  debug_sync.cc
  auth/sql_authentication.cc
  auth/sql_auth_cache.cc
  auth/sql_authorization.cc
  auth/sql_user_table.cc
  auth/sql_user.cc
  auth/sql_security_ctx.cc
  auth/role_tables.cc
  auth/dynamic_privilege_table.cc
  auth/dynamic_privileges_impl.cc
  handler.cc
  ${SQL_GIS_SOURCES}
  spatial.cc
  window.cc
  sql_exception_handler.cc
)
SET(SQL_EXPORTED_BOOST_SOURCES ${SQL_BOOST_SOURCES} PARENT_SCOPE)

INCLUDE(${MYSQL_CMAKE_SCRIPT_DIR}/compile_flags.cmake)
ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES}
  COMPILE_FLAGS -I${BOOST_PATCHES_DIR} -I${BOOST_INCLUDE_DIR})

# warning C4348
# boost::spirit::terminal<boost::spirit::tag::lit>::result_helper': 
#       redefinition of default parameter
IF(WIN32)
  ADD_COMPILE_FLAGS(
    gis/srs/srs.cc
    gis/srs/wkt_parser.cc
    COMPILE_FLAGS "/wd4348")
ENDIF()

# warning 4244 4267
# conversion from 'coordinate_type' to 'const promoted_type
# conversion from 'boost::geometry::signed_size_type' to 'int'
# etc. etc.
IF(WIN32)
  ADD_COMPILE_FLAGS(
    item_geofunc.cc
    item_geofunc_buffer.cc
    item_geofunc_internal.cc
    item_geofunc_setops.cc
    COMPILE_FLAGS "/wd4244" "/wd4267")
ENDIF()

# Segfault in boost::geometry code at high optimization levels
IF(CMAKE_CXX_COMPILER_ID MATCHES "SunPro")
  STRING(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKEBT)
  IF(CMAKEBT MATCHES "^REL")
    ADD_COMPILE_FLAGS(item_geofunc_buffer.cc COMPILE_FLAGS "-xO2")
  ENDIF()
ENDIF()

# Assertion in Developer Studio 12.5 (fixed in 12.6 beta).
IF(CMAKE_CXX_COMPILER_ID MATCHES "SunPro")
  ADD_COMPILE_FLAGS(
    gis/srs/srs.cc
    gis/srs/wkt_parser.cc
    COMPILE_FLAGS "-DBOOST_NO_CXX11_VARIADIC_TEMPLATES"
  )
ENDIF()

ADD_COMPILE_FLAGS(
  ../extra/lz4/xxhash.c
  COMPILE_FLAGS -DXXH_NAMESPACE=MY_
)

# Fixes "C1128: number of sections exceeded object file format limit" in MSVC
IF(WIN32)
  ADD_COMPILE_FLAGS(
    gis/difference.cc
    gis/touches.cc
    gis/within.cc
    item_geofunc.cc
    item_geofunc_setops.cc
    COMPILE_FLAGS "/bigobj")
ENDIF()

#
# Disabling of various compiler warnings for GCC/Clang
#

IF(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Common for all versions of GCC/Clang

  # Bison output and Boost source use undefined symbols in #if checks
  ADD_COMPILE_FLAGS(${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.cc
                    ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.cc
                    ${SQL_BOOST_SOURCES}
                    COMPILE_FLAGS "-Wno-undef")
  # Boost source compares signed and unsigned integer expressions
  ADD_COMPILE_FLAGS(gis/srs/wkt_parser.cc
                    COMPILE_FLAGS "-Wno-sign-compare")
  # Boost source use auto_ptr, deprecated in C++11
  ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES}
                    COMPILE_FLAGS "-Wno-deprecated-declarations")
  # Boost source has unused parameters
  ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES} COMPILE_FLAGS "-Wno-unused-parameter")

  # Only for some versions of GCC/Clang

  MY_CHECK_CXX_COMPILER_FLAG("-Wunused-local-typedefs" HAVE_UNUSED_TYPEDEFS)
  IF(HAVE_UNUSED_TYPEDEFS)
    # Boost source has unused local typedefs.
    ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES}
                      COMPILE_FLAGS "-Wno-unused-local-typedefs")
  ENDIF()
  
  MY_CHECK_CXX_COMPILER_FLAG("-Wlogical-op" HAVE_LOGICAL_OP)
  IF(HAVE_LOGICAL_OP)
    # Boost source has logical && with non-zero constant
    ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES}
                      COMPILE_FLAGS "-Wno-logical-op")
  ENDIF()

  MY_CHECK_CXX_COMPILER_FLAG("-Wplacement-new" HAVE_PLACEMENT_NEW_WARNING)
  IF(HAVE_PLACEMENT_NEW_WARNING)
    # Boost.Spirit causes a warning about placement new on GCC 6. Expected
    # to be fixed upstream by https://github.com/boostorg/function/pull/9.
    ADD_COMPILE_FLAGS(gis/srs/wkt_parser.cc
                      COMPILE_FLAGS "-Wno-placement-new")
  ENDIF()

  MY_CHECK_CXX_COMPILER_FLAG("-Wmisleading-indentation"
                             HAVE_MISLEADING_INDENTATION)
  IF(HAVE_MISLEADING_INDENTATION)
    # Boost source has misleading indentation
    ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES}
                      COMPILE_FLAGS "-Wno-misleading-indentation")
  ENDIF()

  MY_CHECK_CXX_COMPILER_FLAG("-Wmaybe-uninitialized" HAVE_MAYBE_UNINITIALIZED)
  IF(HAVE_MAYBE_UNINITIALIZED)
    # Boost Graph has uninitialized usage
    ADD_COMPILE_FLAGS(${SQL_BOOST_SOURCES}
                      COMPILE_FLAGS "-Wno-maybe-uninitialized")
  ENDIF()
ENDIF()


MY_CHECK_CXX_COMPILER_FLAG("-fno-builtin-memcmp" HAVE_NO_BUILTIN_MEMCMP)
# See comments in filesort_compare-t.cc about __builtin_memcmp
IF(HAVE_NO_BUILTIN_MEMCMP)
  ADD_COMPILE_FLAGS(
    filesort_utils.cc
    COMPILE_FLAGS "-fno-builtin-memcmp"
  )
ENDIF()

IF (WIN32 AND OPENSSL_APPLINK_C)
  ADD_COMPILE_FLAGS(
    ../sql-common/client_authentication.cc
    COMPILE_FLAGS "-DHAVE_OPENSSL_APPLINK_C"
  )
ENDIF()

ADD_CONVENIENCE_LIBRARY(sql_rtree gis/rtree_support.cc)
ADD_CONVENIENCE_LIBRARY(sql_main ${SQL_SOURCE})
ADD_DEPENDENCIES(sql_main GenServerSource)
ADD_DEPENDENCIES(sql_main GenDigestServerSource)
ADD_DEPENDENCIES(sql_main GenBootstrapPriv)
ADD_DEPENDENCIES(sql_main GenSysSchema)
TARGET_LINK_LIBRARIES(sql_main ${MYSQLD_STATIC_PLUGIN_LIBS} 
  ${MYSQLD_STATIC_COMPONENT_LIBS}  mysys mysys_ssl dbug strings vio regex
  binlogevents_static sql_rtree ${LIBWRAP} ${LIBCRYPT} ${LIBDL} ${SSL_LIBRARIES})

ADD_CONVENIENCE_LIBRARY(sql_gis ${SQL_GIS_SOURCES})
ADD_DEPENDENCIES(sql_gis GenServerSource)
ADD_DEPENDENCIES(sql_gis GenDigestServerSource)
ADD_DEPENDENCIES(sql_gis GenBootstrapPriv)
ADD_DEPENDENCIES(sql_gis GenSysSchema)
ADD_DEPENDENCIES(sql_gis GenError)

#
# On Windows platform we compile in the clinet-side Windows Native Authentication
# plugin which is used by the client connection code included in the server.
#
IF(WIN32)
  ADD_DEFINITIONS(-DAUTHENTICATION_WIN)
  TARGET_LINK_LIBRARIES(sql_main auth_win_client)
ENDIF()

SET (BINLOG_SOURCE rpl_gtid_misc.cc
                   rpl_gtid_sid_map.cc rpl_gtid_set.cc rpl_gtid_specification.cc
                   rpl_gtid_state.cc rpl_gtid_owned.cc rpl_gtid_execution.cc
                   rpl_gtid_mutex_cond_array.cc rpl_gtid_persist.cc
                   log_event.cc binlog.cc sql_binlog.cc
                   rpl_filter.cc rpl_record.cc rpl_trx_tracking.cc
                   rpl_utility.cc rpl_injector.cc rpl_table_access.cc)
ADD_CONVENIENCE_LIBRARY(binlog ${BINLOG_SOURCE})
TARGET_LINK_LIBRARIES(binlog binlogevents_static)

SET (RPL_SOURCE rpl_handler.cc rpl_tblmap.cc rpl_context.cc)
ADD_DEPENDENCIES(binlog GenError)
ADD_CONVENIENCE_LIBRARY(rpl ${RPL_SOURCE})
SET (MASTER_SOURCE rpl_master.cc rpl_binlog_sender.cc)
ADD_DEPENDENCIES(rpl GenError)
ADD_CONVENIENCE_LIBRARY(master ${MASTER_SOURCE})
ADD_DEPENDENCIES(master GenError)
SET (SLAVE_SOURCE rpl_slave.cc rpl_reporting.cc rpl_mi.cc rpl_rli.cc
                  rpl_info_handler.cc rpl_info_file.cc
                  rpl_info_table.cc rpl_info_values.cc rpl_info.cc
                  rpl_info_factory.cc rpl_info_table_access.cc dynamic_ids.cc
                  rpl_rli_pdb.cc rpl_info_dummy.cc rpl_mts_submode.cc
                  rpl_slave_commit_order_manager.cc rpl_msr.cc
                  rpl_trx_boundary_parser.cc rpl_channel_service_interface.cc
                  rpl_slave_until_options.cc)
ADD_CONVENIENCE_LIBRARY(slave ${SLAVE_SOURCE})
ADD_DEPENDENCIES(slave GenError)


IF(WIN32)
  SET(MYSQLD_SOURCE main.cc nt_servc.cc nt_servc.h message.rc)
ELSE()
  SET(MYSQLD_SOURCE main.cc)
ENDIF()

MYSQL_ADD_EXECUTABLE(mysqld
  ${MYSQLD_SOURCE} DESTINATION ${INSTALL_SBINDIR} COMPONENT Server)

OPTION(DEBUG_EXTNAME "Build server as mysqld-debug (debug builds only)" OFF)
MARK_AS_ADVANCED(DEBUG_EXTNAME)

IF(DEBUG_EXTNAME)
  SET_TARGET_PROPERTIES(mysqld PROPERTIES DEBUG_OUTPUT_NAME "mysqld-debug")
ENDIF()

IF(APPLE) 
  # Add CoreServices framework since some dloadable plugins may need it 
  FIND_LIBRARY(CORESERVICES NAMES CoreServices) 
  IF(CORESERVICES) 
    TARGET_LINK_LIBRARIES(mysqld ${CORESERVICES}) 
  ENDIF() 
ENDIF() 

IF(NOT DISABLE_SHARED)
  SET_TARGET_PROPERTIES(mysqld PROPERTIES ENABLE_EXPORTS TRUE)
  GET_TARGET_PROPERTY(mysqld_link_flags mysqld LINK_FLAGS)
  IF(NOT mysqld_link_flags)
    SET(mysqld_link_flags)
  ENDIF()
  IF(MSVC)
    # Set module definition file.
    SET_TARGET_PROPERTIES(mysqld PROPERTIES LINK_FLAGS "${mysqld_link_flags} /DEF:mysqld.def")

    FOREACH (CORELIB sql_main binlog slave mysys mysys_ssl dbug regex strings
        vio binlogevents_static)
      GET_TARGET_PROPERTY(LOC ${CORELIB} LOCATION)
      IF (NOT LOC)
        GET_TARGET_PROPERTY(LOC ${CORELIB} IMPORTED_LOCATION)
      ENDIF()


      FILE(TO_NATIVE_PATH ${LOC} LOC)
      SET (LIB_LOCATIONS ${LIB_LOCATIONS} ${LOC}) 
    ENDFOREACH (CORELIB ${MYSQLD_CORE_LIBS})
    SET(_PLATFORM  x64)
    ADD_CUSTOM_COMMAND(TARGET mysqld PRE_LINK
      COMMAND echo ${_PLATFORM} && cscript ARGS //nologo ${PROJECT_SOURCE_DIR}/win/create_def_file.js
                  ${_PLATFORM}  ${LIB_LOCATIONS} > mysqld.def 
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    ADD_DEPENDENCIES(sql_main GenError)
  ENDIF()
ENDIF()

SET_TARGET_PROPERTIES(mysqld PROPERTIES ENABLE_EXPORTS TRUE) 
TARGET_LINK_LIBRARIES(mysqld
  sql_main sql_gis binlog rpl master slave sql_main sql_gis mysys mysys_ssl
  binlogevents_static)

# Remove transitive link dependencies when linking plugins
SET_TARGET_PROPERTIES(mysqld PROPERTIES INTERFACE_LINK_LIBRARIES "")

SET(WITH_MYSQLD_LDFLAGS "" CACHE STRING "Additional linker flags for mysqld")
MARK_AS_ADVANCED(WITH_MYSQLD_LDFLAGS)
IF(WITH_MYSQLD_LDFLAGS)
  GET_TARGET_PROPERTY(mysqld LINK_FLAGS MYSQLD_LINK_FLAGS)
  IF(NOT MYSQLD_LINK_FLAGS)
    SET(MYSQLD_LINK_FLAGS) 
  ENDIF() 
  SET_TARGET_PROPERTIES(mysqld PROPERTIES LINK_FLAGS 
     "${MYSQLD_LINK_FLAGS} ${WITH_MYSQLD_LDFLAGS}")
ENDIF()

IF(DEBUG_EXTNAME)
  INSTALL_DEBUG_TARGET(mysqld 
    DESTINATION ${INSTALL_SBINDIR} 
    PDB_DESTINATION ${INSTALL_SBINDIR}
    SUFFIX "-debug")
ELSE()
  INSTALL_DEBUG_TARGET(mysqld 
    DESTINATION ${INSTALL_SBINDIR} 
    PDB_DESTINATION ${INSTALL_SBINDIR}/debug
    RENAME mysqld-debug)
ENDIF()


# Handle out-of-source build from source package with possibly broken 
# bison. Copy bison output to from source to build directory, if not already 
# there
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/bison.cmake)
COPY_BISON_OUTPUT(
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_yacc.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_yacc.h
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.h
)

COPY_BISON_OUTPUT(
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_hints.yy.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_hints.yy.h
  ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.h
)

RUN_BISON(
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_yacc.yy 
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.h
  MYSQL
)

RUN_BISON(
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_hints.yy 
  ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sql_hints.yy.h
  HINT_PARSER_
)

SET_SOURCE_FILES_PROPERTIES(
  ${CMAKE_CURRENT_BINARY_DIR}/sql_yacc.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/sql_digest.cc
  PROPERTIES OBJECT_DEPENDS ${GEN_DIGEST_SOURCES}
)

# Gen_lex_hash
ADD_EXECUTABLE(gen_lex_hash gen_lex_hash.cc)

ADD_CUSTOM_COMMAND(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lex_hash.h
  COMMAND gen_lex_hash > lex_hash.h
  DEPENDS gen_lex_hash
)

MYSQL_ADD_EXECUTABLE(mysql_tzinfo_to_sql tztime.cc)
SET_TARGET_PROPERTIES(mysql_tzinfo_to_sql PROPERTIES COMPILE_FLAGS "-DTZINFO2SQL")
TARGET_LINK_LIBRARIES(mysql_tzinfo_to_sql mysys mysys_ssl)
ADD_DEPENDENCIES(mysql_tzinfo_to_sql GenError)

ADD_CUSTOM_TARGET( 
        GenServerSource
        DEPENDS ${GEN_SOURCES}
)

ADD_CUSTOM_TARGET( 
        GenDigestServerSource
        DEPENDS ${GEN_DIGEST_SOURCES}
)


MYSQL_ADD_PLUGIN(udf_example udf_example.cc
                 MODULE_ONLY SKIP_INSTALL MODULE_OUTPUT_NAME "udf_example")
IF(NOT DISABLE_SHARED)
  IF(WIN32)
    SET_TARGET_PROPERTIES(udf_example
      PROPERTIES LINK_FLAGS
      "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/udf_example.def")
  ENDIF()
ENDIF()

MYSQL_ADD_PLUGIN(locking_service locking_service_udf.cc
                 MODULE_ONLY MODULE_OUTPUT_NAME "locking_service")
IF(NOT DISABLE_SHARED)
  IF(WIN32)
    SET_TARGET_PROPERTIES(locking_service
      PROPERTIES LINK_FLAGS
      "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/locking_service.def")
  ENDIF()
ENDIF()

FOREACH(tool gtar tar git)
  STRING(TOUPPER ${tool}  TOOL)
  FIND_PROGRAM(${TOOL}_EXECUTABLE ${tool} DOC "path to the executable")
  MARK_AS_ADVANCED(${TOOL}_EXECUTABLE)
ENDFOREACH()

CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/cmake/make_dist.cmake.in
  ${CMAKE_BINARY_DIR}/make_dist.cmake @ONLY)

ADD_CUSTOM_TARGET(dist 
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/make_dist.cmake
  DEPENDS ${CMAKE_BINARY_DIR}/sql/sql_yacc.cc ${CMAKE_BINARY_DIR}/sql/sql_yacc.h ${CMAKE_BINARY_DIR}/sql/sql_hints.yy.cc ${CMAKE_BINARY_DIR}/sql/sql_hints.yy.h
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

ADD_CUSTOM_TARGET(distclean
  COMMAND ${CMAKE_COMMAND} -E echo  WARNING: distclean target is not functional
  COMMAND ${CMAKE_COMMAND} -E echo  Use 'git clean -fdx' instead
  VERBATIM
  )

ADD_CUSTOM_TARGET(show-dist-name
  COMMAND ${CMAKE_COMMAND} -E echo "${CPACK_PACKAGE_FILE_NAME}"
)
