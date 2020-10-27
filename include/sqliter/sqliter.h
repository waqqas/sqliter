#ifndef SQLITER_H
#define SQLITER_H

#include "sqliter/basic_sqlite.h"

namespace sqliter {
namespace asio {

typedef basic_sqlite<basic_sqlite_service<> > sqlite;

}  // namespace asio
}  // namespace sqliter

#endif
