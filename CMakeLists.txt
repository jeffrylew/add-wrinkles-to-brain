cmake_minimum_required(VERSION 3.14)
project(add-wrinkles-to-brain)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  new_year_chaos_test
  new_year_chaos.cpp
)
target_link_libraries(
  new_year_chaos_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(new_year_chaos_test)