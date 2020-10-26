#ifndef BASCI_SQLITE_SERVICE_H
#define BASCI_SQLITE_SERVICE_H

#include "handler_helper.h"
#include "sqlite_impl.h"

#include <boost/asio.hpp>
#include <functional>  // std::bind
#include <list>
#include <stdexcept>  // std::runtime_error
#include <string>
#include <thread>   // std::thread
#include <utility>  // std::pair
namespace waqqas {
namespace asio {

template <typename... T>
class query_result
{
public:
  using data_type_t = std::list<std::tuple<T...>>;
  std::list<std::string> column_names;
  data_type_t            data;
};

template <typename SqliteImplementation = sqlite_impl>
class basic_sqlite_service : public boost::asio::io_service::service
{
public:
  static boost::asio::io_service::id id;

  explicit basic_sqlite_service(boost::asio::io_service &io_service)
    : boost::asio::io_service::service(io_service)
    , io_service_(io_service)
  {}

  ~basic_sqlite_service()
  {}

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

  void open(implementation_type &impl, const std::string &db_name)
  {
    impl->open(db_name);
  }

  template <typename Handler>
  void async_query(implementation_type &impl, const std::string &sql, Handler &handler)
  {
    boost::system::error_code ec = boost::system::error_code();

    using traits         = function_traits<Handler>;
    using query_result_t = typename traits::template arg<1>::type;

    query_result_t result;
    try
    {
      sqlite_impl::query_handler qh{[&result](int num_columns, char **data, char **columns) {
        int i = 0;

        assert(num_columns == std::tuple_size<typename query_result_t::data_type_t::value_type>::value);
        
        for (i = 0; i < num_columns; i++)
        {
          // result.data.push_back(std::make_tuple());
        }
      }};

      impl->query(sql, qh);
      this->io_service_.post(std::bind(handler, ec, result));
    }
    catch (const std::exception &e)
    {
      ec = boost::asio::error::operation_aborted;
      this->io_service_.post(std::bind(handler, ec, result));
    }
  }

private:
  boost::asio::io_service &io_service_;
};

template <typename SqliteImplementation>
boost::asio::io_service::id basic_sqlite_service<SqliteImplementation>::id;

}  // namespace asio
}  // namespace waqqas
#endif