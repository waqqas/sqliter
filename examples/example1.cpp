
#include "boost_sqlite.h"

#include <iostream>

using namespace waqqas::asio;

int main(int argc, char* argv[])
{
  boost::asio::io_service io;
  sqlite                  db(io);

  using app_table_result = query_result<int32_t, int32_t>;

  db.open(argv[1]);

  db.async_query("SELECT * from app",
                 [](const boost::system::error_code &ec, const app_table_result result) {
                   if (!ec)
                   {
                     app_table_result::data_type_t::const_iterator it;

                     std::cout << "result size: " << result.data.size() << std::endl;

                     for (it = result.data.begin(); it != result.data.end(); ++it)
                     {
                       std::cout << "value 0: " << std::get<0>(*it) << std::endl;
                     }
                   }
                 });

  io.run();

  return 0;
}