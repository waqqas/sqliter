
#include "sqliter/sqliter.h"

#include <iostream>
#include <string>
using namespace sqliter::asio;

struct async_query_initiation
{
  template <typename CompletionHandler>
  void operator()(CompletionHandler &&completion_handler, sqlite &db,
                  const std::string &query) const
  {
    auto executor = boost::asio::get_associated_executor(completion_handler);

    db.async_query(query,
                   boost::asio::bind_executor(
                       executor, std::bind(std::forward<CompletionHandler>(completion_handler),
                                           std::placeholders::_1)));
  }
};

template <typename CompletionToken>
auto async_query(sqlite &db, const std::string &query, CompletionToken &&token) ->
    typename boost::asio::async_result<typename std::decay<CompletionToken>::type,
                                       void(boost::system::error_code)>::return_type
{
  return boost::asio::async_initiate<CompletionToken, void(boost::system::error_code)>(
      async_query_initiation(), token, db, query);
}

int main(int argc, char *argv[])
{
  boost::asio::io_service io;
  sqlite                  db(io);

  if (argc != 2)
  {
    std::cout << argv[0] << " <sqlite db file>" << std::endl;
    return -1;
  }

  db.open(argv[1]);

  std::future<void> f = async_query(db, "SELECT * from app", boost::asio::use_future);

  io.run();

  try
  {
    // Get the result of the operation.
    f.get();
    std::cout << "success" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }

  boost::system::error_code ec = {};
  db.close(ec);

  return 0;
}