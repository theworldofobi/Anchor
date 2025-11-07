cmake_minimum_required(VERSION 3.0)

project(Anchor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(Common)
add_subdirectory(Exchange)
add_subdirectory(Trading)

list(APPEND LIBS libexchange)
list(APPEND LIBS libcommon)
list(APPEND LIBS libtrading)
list(APPEND LIBS pthread)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Exchange)
include_directories(${PROJECT_SOURCE_DIR}/Trading)

add_executable(ExchangeMain Exchange/ExchangeMain.cpp)
target_link_libraries(ExchangeMain PUBLIC ${LIBS})

