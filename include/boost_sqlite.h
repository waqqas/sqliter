#ifndef BOOST_SQLITE_H
#define BOOST_SQLITE_H

#include "basic_sqlite.h"

namespace waqqas {
namespace asio {

typedef basic_sqlite<basic_sqlite_service<> > sqlite;

}  // namespace asio
}  // namespace boost

#endif
