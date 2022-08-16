set(
  hr_puzzles
  "binary_tree_inorder_traversal"
  "binary_tree_level_order_traversal"
  "binary_tree_postorder_traversal"
  "binary_tree_preorder_traversal"
  "height_of_a_binary_tree"
  "huffman_decoding"
  "is_this_a_binary_search_tree"
  "lowest_common_ancestor"
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