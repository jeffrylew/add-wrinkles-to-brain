set(
  hr_puzzles
  "a_very_big_sum"
  "birthday_cake_candles"
  "breaking_the_records"
  "compare_the_triplets"
  "diagonal_difference"
  "grading_students"
  "mini_max_sum"
  "number_line_jumps"
  "plus_minus"
  "simple_array_sum"
  "staircase"
  "time_conversion"
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