set(
  hr_puzzles
  "find_merge_point_of_two_lists"
  "insert_a_node"
  "insert_a_node_into_a_sorted_doubly_linked_list"
  "reverse_a_doubly_linked_list"
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