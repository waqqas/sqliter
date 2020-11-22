
#include "sqliter/sqliter.h"

#include <iostream>
#include <string>
using namespace sqliter::asio;

int main(int argc, char *argv[])
{
  boost::asio::io_service io;
  sqlite                  db(io);

  using app_table_result = query_result<int32_t, int32_t, std::string, float>;

  if (argc != 2)
  {
    std::cout << argv[0] << " <sqlite db file>" << std::endl;
    return -1;
  }

  db.open(argv[1]);

  boost::system::error_code ec;
  app_table_result          result;

  db.query("SELECT * from app", ec, result);
  if (!ec)
  {
    app_table_result::query_data_type::const_iterator it;

    std::cout << "result size: " << result.data.size() << std::endl;

    for (it = result.data.begin(); it != result.data.end(); ++it)
    {
      std::cout << "ID: " << std::get<0>(*it) << ", state: " << std::get<1>(*it)
                << ", data: " << std::get<2>(*it) << ", float: " << std::get<3>(*it) << std::endl;
    }
  }

  io.run();

  db.close(ec);

  return 0;
}