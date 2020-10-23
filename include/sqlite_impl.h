#ifndef BASIC_SQLITE_IMPL_H
#define BASIC_SQLITE_IMPL_H

#include <sqlite3.h>
#include <string>

namespace boost {
namespace asio {

  using query_cb_type = std::function<void(int, char **, char **)>;

  struct query_handler {
    query_cb_type callback;
  };

static int query_callback(void *h, int argc, char **argv, char **azColName) {
  query_handler *handler = (query_handler *)h;
  if (handler->callback != nullptr) {
    handler->callback(argc, argv, azColName);
  }
  return 0;
}


class sqlite_impl
{
public:
  sqlite_impl()
  {}

  ~sqlite_impl()
  {
    if (_db)
    {
      sqlite3_close(_db);
    }
  }

  void open(const std::string &db_name)
  {
    if (sqlite3_open(db_name.c_str(), &_db) != SQLITE_OK)
    {
      throw std::runtime_error(sqlite3_errmsg(_db));
    }
  }
  void destroy()
  {
    sqlite3_close(_db);
    _db = nullptr;
  }

  void query(const std::string &sql, const query_handler handler)
  {
    char *zErrMsg;

    int rc = sqlite3_exec(_db, sql.c_str(), query_callback, (void*)&handler, &zErrMsg);
    if (rc != SQLITE_OK)
    {
      std::string error = zErrMsg;
      sqlite3_free(zErrMsg);
      throw std::runtime_error(error);
    }
  }

private:
  sqlite3 *_db;
};
}  // namespace asio
}  // namespace boost

#endif
