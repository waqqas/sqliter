project(example1)

set(SOURCES example1.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(sqliter CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} sqliter::sqliter)

find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(${PROJECT_NAME} Boost::system)

find_package(SQLite3 REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} SQLite::SQLite3)