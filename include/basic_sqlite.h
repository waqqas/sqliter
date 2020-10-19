#ifndef BASIC_SQLITE_H
#define BASIC_SQLITE_H

#include <boost/asio.hpp>
#include "basic_sqlite_service.h"

namespace boost {
namespace asio {

template <typename Service>
class basic_sqlite : public boost::asio::basic_io_object<Service>
{
public:
  explicit basic_sqlite(boost::asio::io_service &io_service)
    : boost::asio::basic_io_object<Service>(io_service)
  {}
};

}  // namespace asio
}  // namespace boost
#endif