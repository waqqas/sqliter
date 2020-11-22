
#include "sqliter/sqliter.h"

#include <iostream>
#include <string>
using namespace sqliter::asio;

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

  boost::system::error_code ec;

  db.query("SELECT * from app", ec);
  std::cout << "Result: " << ec.message() << std::endl;

  io.run();

  db.close(ec);

  return 0;
}