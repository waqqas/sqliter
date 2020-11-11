# SQLiter

Boost SQLite3 custom io service

Building library
---

- `mkdir build`
- `cd build`
- `cmake -DCMAKE_INSTALL_PREFIX:PATH=`pwd`/usr ..`
- `cmake --build . --config Release --target install -- -j $(nproc)`

Building examples
---

After building library
- `cmake -DSQLITER_BUILD_EXAMPLES:BOOL=ON ..`
- `cmake --build . --config Release -- -j $(nproc)`

Running example
---
- `sqlite3 ./test.db < ../test.db.sql`
- `./examples/example1 ./test.db`

Usage
---

Steps
- Include header file
- Import namespace
- Declare sqlite variable
- Define result-set structure
- Open database
- Add query task
- Run io service

```

#include "sqliter/sqliter.h"

using namespace sqliter::asio;

  boost::asio::io_service io;
  sqlite                  db(io);

  using app_table_result = query_result<int32_t, int32_t>;

  db.open('test.db');

  db.async_query(
      "SELECT * from app", [](const boost::system::error_code &ec, const app_table_result result) {
        if (!ec)
        {
          app_table_result::query_data_type::const_iterator it;

          std::cout << "result size: " << result.data.size() << std::endl;

          for (it = result.data.begin(); it != result.data.end(); ++it)
          {
            std::cout << "ID: " << std::get<0>(*it) << ", state: " << std::get<1>(*it) << std::endl;
          }
        }
      });

  io.run();


```