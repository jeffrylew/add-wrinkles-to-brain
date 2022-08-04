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

add_subdirectory(arrays)
# add_subdirectory(dynamic_programming)
# add_subdirectory(graphs)
add_subdirectory(greedy_algorithms)
# add_subdirectory(linked_lists)
add_subdirectory(maps)
# add_subdirectory(miscellaneous)
# add_subdirectory(recursion)
add_subdirectory(search)
add_subdirectory(sorting)
add_subdirectory(stacks_and_queues)
add_subdirectory(string_manipulation)
add_subdirectory(trees)