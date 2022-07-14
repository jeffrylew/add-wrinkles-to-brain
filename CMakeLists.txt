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
  "alternating_characters"
  "bubble_sort"
  "comparator"
  "count_triplets"
  "mark_and_toys"
  "minimum_swaps_2"
  "new_year_chaos"
  "ransom_note"
  "sherlock_and_anagrams"
  "two_strings"
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