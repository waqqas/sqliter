
#include "boost_sqlite.h"

using namespace boost::asio;

int main(void)
{
    io_service io;
    boost::asio::sqlite query(io);

    return 0;
}