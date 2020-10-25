
#include "boost_sqlite.h"


using namespace waqqas::asio;

int main(void)
{
    boost::asio::io_service io;
    sqlite db(io);

    db.open("test.db");

    db.async_query("SELECT * from app", [](const boost::system::error_code&, const query_result& result){});

    return 0;
}