set(
  hr_puzzles
  "alternating_characters"
  "making_anagrams"
  "sherlock_and_the_valid_string"
  "special_string_again"
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