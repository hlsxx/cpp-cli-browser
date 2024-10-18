cmake_minimum_required(VERSION 3.10)

project(CppCliBrowser VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(MyApp
  src/main.cpp
  src/cli_handler/cli_handler.cpp
  src/search_handler/search_handler.cpp
  src/file_handler/file_handler.cpp
)

target_include_directories(MyApp PUBLIC
  ${CMAKE_SOURCE_DIR}/src/cli_handler
  ${CMAKE_SOURCE_DIR}/src/search_handler
  ${CMAKE_SOURCE_DIR}/src/file_handler
)
