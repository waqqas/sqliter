project(example1)

set(SOURCES example1.cpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost REQUIRED COMPONENTS system)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(${PROJECT_NAME} Boost::system)

find_package(SQLite3 REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME}  SQLite::SQLite3)