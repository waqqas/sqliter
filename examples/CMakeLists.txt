project(example1)

set(SOURCES example1.cpp)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(${PROJECT_NAME} Boost::system)
