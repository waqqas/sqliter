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

