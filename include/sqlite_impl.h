#ifndef BASIC_SQLITE_IMPL_H
#define BASIC_SQLITE_IMPL_H

#include <sqlite3.h>
#include <string>

namespace boost {
namespace asio {

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
  {}

  template<typename Handler>
  void async_query(const std::string& sql, Handler handler){}

private:
  sqlite3 *_db;
};
}  // namespace asio
}  // namespace boost

#endif
