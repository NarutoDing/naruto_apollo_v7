/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#include "modules/common/kv_db/kv_db.h"

#include <sqlite3.h>

#include "gflags/gflags.h"

#include "absl/strings/str_cat.h"
#include "cyber/common/log.h"
#include "modules/common/util/util.h"

DEFINE_string(kv_db_path, "/apollo/data/kv_db.sqlite",
              "Path to Key-value DB file.");

namespace apollo {
namespace common {
namespace {

// Self-maintained sqlite instance.
class SqliteWraper {
 public:
  static int Callback(void *data, int argc, char **argv, char **col_name) {
    if (data != nullptr) {
      std::string *data_str = static_cast<std::string *>(data);
      *data_str = argc > 0 ? argv[0] : "";
    }
    return 0;
  }

  SqliteWraper() {
    // Open DB.
    if (sqlite3_open(FLAGS_kv_db_path.c_str(), &db_) != 0) {
      AERROR << "Can't open Key-Value database: " << sqlite3_errmsg(db_);
      Release();
      return;
    }

    // Create table if it doesn't exist.
    static const char *kCreateTableSql =
        "CREATE TABLE IF NOT EXISTS key_value "
        "(key VARCHAR(128) PRIMARY KEY NOT NULL, value TEXT);";
    if (!SQL(kCreateTableSql)) {
      Release();
    }
  }

  ~SqliteWraper() { Release(); }

  bool SQL(std::string_view sql, std::string *value = nullptr) {
    AINFO << "Executing SQL: " << sql;
    if (db_ == nullptr) {
      AERROR << "DB is not open properly.";
      return false;
    }

    char *error = nullptr;
    if (sqlite3_exec(db_, sql.data(), Callback, value, &error) != SQLITE_OK) {
      AERROR << "Failed to execute SQL: " << error;
      sqlite3_free(error);
      return false;
    }
    return true;
  }

 private:
  void Release() {
    if (db_ != nullptr) {
      sqlite3_close(db_);
      db_ = nullptr;
    }
  }

  sqlite3 *db_ = nullptr;
};

}  // namespace

bool KVDB::Put(std::string_view key, std::string_view value) {
  SqliteWraper sqlite;
  return sqlite.SQL(
      absl::StrCat("INSERT OR REPLACE INTO key_value (key, value) VALUES ('",
                   key, "', '", value, "');"));
}

bool KVDB::Delete(std::string_view key) {
  SqliteWraper sqlite;
  return sqlite.SQL(
      absl::StrCat("DELETE FROM key_value WHERE key='", key, "';"));
}

std::optional<std::string> KVDB::Get(std::string_view key) {
  SqliteWraper sqlite;
  std::string value;
  const bool ret = sqlite.SQL(
      absl::StrCat("SELECT value FROM key_value WHERE key='", key, "';"),
      &value);
  if (ret && !value.empty()) {
    return value;
  }
  return {};
}

}  // namespace common
}  // namespace apollo
