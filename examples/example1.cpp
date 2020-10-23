
#include "boost_sqlite.h"


using namespace boost::asio;

int main(void)
{
    io_service io;
    boost::asio::sqlite db(io);

    db.open("test.db");

    db.async_query("SELECT * from app", [](const boost::system::error_code&){});

    return 0;
}