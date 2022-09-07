#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! Forward declarations
std::vector<int> combineSortedVectorsIC(const std::vector<int>& vec1,
                                        const std::vector<int>& vec2);

void TopDownSplitMerge(std::vector<int>& B,
                       int               iBegin,
                       int               iEnd,
                       std::vector<int>& A);

void TopDownMerge(const std::vector<int>& A,
                  int                     iBegin,
                  int                     iMid,
                  int                     iEnd,
                  std::vector<int>&       B);

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

//! @brief Top-down merge sort from https://en.wikipedia.org/wiki/Merge_sort
//! @param[in,out] A Reference to vector of items to sort
static void TopDownMergeSort(std::vector<int>& A)
{
    //! Vector B is a work vector, one-time copy of elements from A to B
    auto B = A;

    //! Sort data from B into A
    TopDownSplitMerge(B, 0, A.size(), A);
}

//! Split A into two lists. Sort both lists into B, merge both lists from B to A
//! iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(std::vector<int>& B,
                       int               iBegin,
                       int               iEnd,
                       std::vector<int>& A)
{
    //! Base case: Single element vector is already sorted
    if (iEnd - iBegin <= 1)
    {
        return;
    }
    
    //! Split the list into halves
    auto iMid = (iEnd + iBegin) / 2;

    //! Recursively sort both halves from A into B
    TopDownSplitMerge(A, iBegin, iMid, B);
    TopDownSplitMerge(A, iMid, iEnd, B);

    //! Merge resulting halves from B into A
    TopDownMerge(B, iBegin, iMid, iEnd, A);

} // void TopDownSplitMerge( ...

//! Left source half is  A[iBegin:iMid - 1]
//! Right source half is A[iMid:iEnd - 1]
//! Result is            B[iBegin:iEnd - 1]
void TopDownMerge(const std::vector<int>& A,
                  int                     iBegin,
                  int                     iMid,
                  int                     iEnd,
                  std::vector<int>&       B)
{
    auto LHS_idx = iBegin;
    auto RHS_idx = iMid;

    //! While there are elements in the LHS or RHS lists...
    for (int k = iBegin; k < iEnd; ++k)
    {
        //! If first element in LHS list exists and is <= first element in RHS
        //! RHS_idx >= iEnd means all elements in RHS list have been processed
        if (LHS_idx < iMid && (RHS_idx >= iEnd || A[LHS_idx] <= A[RHS_idx]))
        {
            B[k] = A[LHS_idx++];
        }
        else
        {
            B[k] = A[RHS_idx++];
        }
    }

} // void TopDownMerge( ...

TEST(MergeSortTest, TestSimple) {
    const std::vector<int> expected {1, 2, 3, 4, 7, 8, 9};

    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           mergeSortIC({8, 3, 2, 7, 9, 1, 4}).cbegin()));
    
    std::vector<int> input {8, 3, 2, 7, 9, 1, 4};
    TopDownMergeSort(input);
    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           input.cbegin()));
}

TEST(MergeSortTest, TestSingleElement) {
    const std::vector<int> expected {7};

    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           mergeSortIC({7}).cbegin()));
    
    std::vector<int> input {7};
    TopDownMergeSort(input);
    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           input.cbegin()));
}

TEST(MergeSortTest, TestVectorReversed) {
    const std::vector<int> expected {1, 2, 3, 4, 5};

    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           mergeSortIC({5, 4, 3, 2, 1}).cbegin()));
    
    std::vector<int> input {5, 4, 3, 2, 1};
    TopDownMergeSort(input);
    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           input.cbegin()));
}

TEST(MergeSortTest, TestVectorAlreadySorted) {
    const std::vector<int> expected {1, 2, 3, 4, 5};

    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           mergeSortIC({1, 2, 3, 4, 5}).cbegin()));
    
    std::vector<int> input {1, 2, 3, 4, 5};
    TopDownMergeSort(input);
    EXPECT_TRUE(std::equal(expected.cbegin(),
                           expected.cend(),
                           input.cbegin()));
}