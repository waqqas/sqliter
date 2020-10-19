#ifndef BASIC_SQLITE_H
#define BASIC_SQLITE_H

#include "basic_sqlite_service.h"

#include <boost/asio.hpp>
#include <string>

namespace boost {
namespace asio {

template <typename Service>
class basic_sqlite : public boost::asio::basic_io_object<Service>
{
public:
  explicit basic_sqlite(boost::asio::io_service &io_service)
    : boost::asio::basic_io_object<Service>(io_service)
  {
  }

  void open(const std::string& db_name)
  {
      this->get_service().open(this->get_implementation(), db_name);
  }
};

}  // namespace asio
}  // namespace boost
#endif