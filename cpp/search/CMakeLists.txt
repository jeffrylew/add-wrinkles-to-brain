set(
  hr_puzzles
  "ice_cream_parlor"
  "making_candies"
  "maximum_subarray"
  "maximum_subarray_sum"
  "minimum_time_required"
  "pairs"
  "swap_nodes_algo"
  "triple_sum"
)

foreach(puzzle IN ITEMS ${hr_puzzles})
  add_executable(
    ${puzzle}_test
    ${puzzle}.cpp
  )

  target_link_libraries(
    ${puzzle}_test
    PRIVATE
    gtest_main
  )
endforeach()

include(GoogleTest)

foreach(puzzle IN ITEMS ${hr_puzzles})
  gtest_discover_tests(${puzzle}_test)
endforeach()