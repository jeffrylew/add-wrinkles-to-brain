#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! Forward declaration
std::vector<int> combineSortedVectorsIC(const std::vector<int>& vec1,
                                        const std::vector<int>& vec2);

//! @brief Merge sort from https://www.interviewcake.com/concept/cpp/merge-sort
static std::vector<int> mergeSortIC(const std::vector<int>& vec)
{
    //! Base case: Single element vector is already sorted
    if (vec.size() <= 1ULL)
    {
        return vec;
    }
    
    //! Split input in half, there is copying of vectors here
    const int mid {static_cast<int>(vec.size()) / 2};
    const std::vector<int> left(vec.begin(), vec.begin() + mid);
    const std::vector<int> right(vec.begin() + mid, vec.end());

    //! Sort each half, there is creation of vectors here again
    auto leftSorted  = mergeSortIC(left);
    auto rightSorted = mergeSortIC(right);

    //! Merge sorted halves
    return combineSortedVectorsIC(leftSorted, rightSorted);

} // static std::vector<int> mergeSortIC( ...

//! @brief Auxiliary function for merging two vectors
std::vector<int> combineSortedVectorsIC(const std::vector<int>& vec1,
                                        const std::vector<int>& vec2)
{
    //! @details https://www.interviewcake.com/concept/cpp/merge-sort

    std::size_t vec1_idx {};
    std::size_t vec2_idx {};
    std::size_t merged_vec_idx {};

    std::vector<int> mergedVector(vec1.size() + vec2.size());

    //! Both input vectors have some items left in them
    while (vec1_idx < vec1.size() && vec2_idx < vec2.size())
    {
        //! Pick smaller of two elements and add to merged vector
        if (vec1[vec1_idx] <= vec2[vec2_idx])
        {
            mergedVector[merged_vec_idx] = vec1[vec1_idx++];
        }
        else
        {
            mergedVector[merged_vec_idx] = vec2[vec2_idx++]; 
        }
        ++merged_vec_idx;

    } // while (vec1_idx < vec1.size() && ...
    
    //! Merge remaining items in vec1 after vec2 has been emptied
    while (vec1_idx < vec1.size())
    {
        mergedVector[merged_vec_idx] = vec1[vec1_idx++];
        ++merged_vec_idx;
    }

    //! Merge remaining items in vec2 after vec1 has been emptied
    while (vec2_idx < vec2.size())
    {
        mergedVector[merged_vec_idx] = vec2[vec2_idx++];
        ++merged_vec_idx;
    }

    return mergedVector;

} // std::vector<int> combineSortedVectorsIC( ...

TEST(MergeSortTest, TestInterviewCake) {
    const std::vector<int> expected {1, 2, 3, 4, 7, 8, 9};

    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           mergeSortIC({8, 3, 2, 7, 9, 1, 4}).cbegin()));
}