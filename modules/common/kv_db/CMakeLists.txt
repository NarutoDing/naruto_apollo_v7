cmake_minimum_required(VERSION 3.16)

project(modules_common_kv_db)
message("${Green} [info] modules_common_kv_db cmakelist ${ColourReset}")

add_library(modules_common_kv_db_kv_db  SHARED
  kv_db.cc
)
set_target_properties(modules_common_kv_db_kv_db  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_kv_db_kv_db
  cyber::common::log
  modules::common::util::util
  modules::common::util::future
  ${gflags_LIBRARIES}
  ${absl}
  ${sqlite3}
)
add_library(modules::common::kv_db::kv_db  ALIAS   modules_common_kv_db_kv_db)

add_executable(kv_db_tool
  kv_db_tool.cc
)
target_link_libraries(kv_db_tool
  modules::common::kv_db::kv_db
)
