#ifndef BASCI_SQLITE_SERVICE_H
#define BASCI_SQLITE_SERVICE_H

#include "sqlite_impl.h"

#include <boost/asio.hpp>
#include <functional>  // std::bind
#include <thread>      // std::thread

namespace boost {
namespace asio {

template <typename SqliteImplementation = sqlite_impl>
class basic_sqlite_service : public boost::asio::io_service::service
{
public:
  static boost::asio::io_service::id id;

  explicit basic_sqlite_service(boost::asio::io_service &io_service)
    : boost::asio::io_service::service(io_service)
  {}

  ~basic_sqlite_service()
  {
  }

  typedef std::shared_ptr<SqliteImplementation> implementation_type;

  void construct(implementation_type &impl)
  {
    impl.reset(new SqliteImplementation());
  }

  void destroy(implementation_type &impl)
  {
    // If an asynchronous call is currently waiting for an event
    // we must interrupt the blocked call to make sure it returns.
    impl->destroy();

    impl.reset();
  }

private:
  boost::asio::io_service                          async_monitor_io_service_;
};

template <typename SqliteImplementation>
boost::asio::io_service::id basic_sqlite_service<SqliteImplementation>::id;

}  // namespace asio
}  // namespace boost
#endif