set(
  hr_puzzles
  "bubble_sort"
  "comparator"
  "counting_sort"
  "fraudulent_activity_notifications"
  "mark_and_toys"
  "merge_sort"
  "merge_sort_counting_inversions"
  "selection_sort"
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