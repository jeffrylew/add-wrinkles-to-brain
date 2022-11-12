set(
  hr_puzzles
  "a_very_big_sum"
  "birthday_cake_candles"
  "compare_the_triplets"
  "diagonal_difference"
  "mini_max_sum"
  "plus_minus"
  "simple_array_sum"
  "staircase"
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