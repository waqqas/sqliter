#ifndef SQLITER_BASIC_SQLITE_SERVICE_H
#define SQLITER_BASIC_SQLITE_SERVICE_H

#include "sqliter/handler_helper.h"
#include "sqliter/query_result.h"
#include "sqliter/sqlite_impl.h"

#include <boost/asio.hpp>
#include <boost/core/ignore_unused.hpp>
#include <functional>  // std::bind
#include <stdexcept>   // std::runtime_error
#include <string>      // std::string

namespace sqliter {
namespace asio {

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

    using traits            = function_traits<Handler>;
    using query_result_type = typename traits::template arg<1>::type;

    query_result_type result;
    try
    {
      sqlite_impl::query_handler qh{[&result](int num_columns, char **data, char **) {
        boost::ignore_unused(num_columns);
        assert(num_columns == std::tuple_size<typename query_result_type::result_data_type>::value);
        result.data.push_back(query_result_type::make_tuple_from_data(data));
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

  template <typename query_result_type>
  void query(implementation_type &impl, const std::string &sql, boost::system::error_code &ec,
             query_result_type &result)
  {
    ec = boost::system::error_code();

    try
    {
      sqlite_impl::query_handler qh{[&result](int num_columns, char **data, char **) {
        boost::ignore_unused(num_columns);
        assert(num_columns == std::tuple_size<typename query_result_type::result_data_type>::value);
        result.data.push_back(query_result_type::make_tuple_from_data(data));
      }};

      impl->query(sql, qh);
    }
    catch (const std::exception &e)
    {
      ec = boost::asio::error::operation_aborted;
    }
  }

  void query(implementation_type &impl, const std::string &sql, boost::system::error_code &ec)
  {
    ec = boost::system::error_code();

    try
    {
      impl->query(sql);
    }
    catch (const std::exception &e)
    {
      ec = boost::asio::error::operation_aborted;
    }
  }

  void close(implementation_type &impl, boost::system::error_code &ec)
  {
    ec = boost::system::error_code();

    try
    {
      impl->destroy();
    }
    catch (const std::exception &e)
    {
      ec = boost::asio::error::operation_aborted;
    }
  }

private:
  boost::asio::io_service &io_service_;
};

template <typename SqliteImplementation>
boost::asio::io_service::id basic_sqlite_service<SqliteImplementation>::id;

}  // namespace asio
}  // namespace sqliter
#endif