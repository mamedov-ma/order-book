cmake_minimum_required(VERSION 3.22)
project(order_book)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic")

add_executable(ORDER_BOOK
    ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/order_book.cpp
)

target_include_directories(ORDER_BOOK PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
