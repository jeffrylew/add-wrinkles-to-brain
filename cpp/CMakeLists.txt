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

set(
  hr_puzzles
  "arrays/2d_array_ds"
  "arrays/minimum_swaps_2"
  "arrays/new_year_chaos"
  "maps/count_triplets"
  "maps/ransom_note"
  "maps/sherlock_and_anagrams"
  "maps/two_strings"
  "sorting/bubble_sort"
  "sorting/comparator"
  "sorting/counting_sort"
  "sorting/fraudulent_activity_notifications"
  "sorting/mark_and_toys"
  "string_manipulation/alternating_characters"
)

foreach(puzzle IN ITEMS ${hr_puzzles})
  add_executable(
    ${puzzle}_test
    ${puzzle}.cpp
  )

  target_link_libraries(
    ${puzzle}_test
    gtest_main
  )
endforeach()

include(GoogleTest)

foreach(puzzle IN ITEMS ${hr_puzzles})
  gtest_discover_tests(${puzzle}_test)
endforeach()