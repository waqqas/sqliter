project(example1)

set(SOURCES example1.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(${PROJECT_NAME} Boost::system)

find_package(SQLite3 REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} SQLite::SQLite3)

project(example2)

set(SOURCES example2.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(${PROJECT_NAME} Boost::system)

find_package(SQLite3 REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} SQLite::SQLite3)

project(example3)

set(SOURCES example3.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(${PROJECT_NAME} Boost::system)

find_package(SQLite3 REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} SQLite::SQLite3)
