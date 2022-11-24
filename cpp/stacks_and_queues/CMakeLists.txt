set(
  hr_puzzles
  "a_tale_of_two_stacks"
  "balanced_brackets"
  "castle_on_the_grid"
  "largest_rectangle"
  "min_max_riddle"
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