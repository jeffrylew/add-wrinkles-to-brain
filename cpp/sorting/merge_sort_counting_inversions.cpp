#include <gtest/gtest.h>

#include <vector>

//! Forward declarations
void top_down_split_merge(long&             num_inversions,
                          std::vector<int>& B,
                          int               iBegin,
                          int               iEnd,
                          std::vector<int>& A);

void top_down_merge(long&                   num_inversions,
                    const std::vector<int>& A,
                    int                     iBegin,
                    int                     iMid,
                    int                     iEnd,
                    std::vector<int>&       B);

long countInversionsDS(std::vector<int>& arr,
                       int               lo,
                       int               hi,
                       std::vector<int>& aux);

long mergeDS(std::vector<int>&       arr,
             int                     lo,
             int                     hi,
             const std::vector<int>& aux);

//! @brief First attempt solution doesn't pass any test cases, needs work
static long countInversionsFirstAttempt(std::vector<int> arr)
{
    long num_inversions {};
    
    if (arr.size() < 2ULL)
    {
        //! Vector of size 1 or less has no inversions
        return num_inversions;
    }
    
    //! Vector B is a work vector, one-time copy of elements from arr to B
    auto B = arr;
    
    top_down_split_merge(num_inversions, B, 0, arr.size(), arr);
    
    return num_inversions;

} // static long countInversionsFirstAttempt( ...

void top_down_split_merge(long&             num_inversions,
                          std::vector<int>& B,
                          int               iBegin,
                          int               iEnd,
                          std::vector<int>& A)
{
    //! Base case: Single element vector already sorted
    if (iEnd - iBegin <= 1)
    {
        return;
    }
    
    //! Split input in halves
    auto iMid = (iEnd + iBegin) / 2;
    
    //! Recursively sort both halves from A into B
    top_down_split_merge(num_inversions, A, iBegin, iMid, B);
    top_down_split_merge(num_inversions, A, iMid, iEnd, B);
    
    //! Merge halves from B into A and keep track of inversions
    top_down_merge(num_inversions, B, iBegin, iMid, iEnd, A);
}

void top_down_merge(long&                   num_inversions,
                    const std::vector<int>& A,
                    int                     iBegin,
                    int                     iMid,
                    int                     iEnd,
                    std::vector<int>&       B)
{
    auto LHS_idx = iBegin;
    auto RHS_idx = iMid;
    
    for (int k = iBegin; k < iEnd; ++k)
    {
        if (LHS_idx < iMid)
        {
            if (RHS_idx >= iEnd)
            {
                //! All elements in RHS have been exhausted
                //! Remaining elements in LHS are inversions
                //! since they need to be placed to the right
                //! of the RHS elements
                B[k] = A[LHS_idx++];
                ++num_inversions;
            }
            else if (A[LHS_idx] <= A[RHS_idx])
            {
                //! Case where elements remain in LHS and RHS
                //! Element in LHS in smaller than element in RHS
                //! No inversions here since no swapping sides
                B[k] = A[LHS_idx++];
            }
            else
            {
                //! Case where elements remain in LHS and RHS
                //! Current element in LHS is larger than
                //! element in RHS. Need to swap RHS to the
                //! left side so this is an inversion
                B[k] = A[RHS_idx++];
                ++num_inversions;
            }
        }
        else
        {
            //! All elements in LHS have been exhausted
            //! Elements in RHS are already to the right
            //! of those in LHS so no swapping needed.
            //! No inversions here
            B[k] = A[RHS_idx++];
        }

    } // for (int k = iBegin; ...

} // void top_down_merge( ...

static long countInversionsDiscussionSolution(std::vector<int> arr)
{
    if (arr.size() < 2ULL)
    {
        //! Vector of size 1 or less has no inversions
        return num_inversions;
    }
    
    //! Vector aux is a work vector, one-time copy of elements from arr to aux
    auto aux = arr;
    
    return countInversionsDS(arr, 0, arr.size() - 1, aux);

} // static long countInversionsDiscussionSolution( ...

long countInversionsDS(std::vector<int>& arr,
                       int               lo,
                       int               hi,
                       std::vector<int>& aux)
{
    if (lo >= hi)
    {
        return 0L;
    }
    
    auto mid = lo + (hi - lo) / 2;
    long num_inversions {};

    num_inversions += countInversionsDS(aux, lo, mid, arr);
    num_inversions += countInversionsDS(aux, mid + 1, hi, arr);
    num_inversions += mergeDS(arr, lo, mid, hi, aux);

    return num_inversions;

} // long countInversionsDS( ...

long mergeDS(std::vector<int>&       arr,
             int                     lo,
             int                     hi,
             const std::vector<int>& aux)
{
    long num_inversions {};
    int  i = lo;
    int  j = mid + 1;
    int  k = lo;

    while (i <= mid || j <= hi)
    {
        if (i > mid)
        {
            //! True if j <= hi
            //! Processed all elements in LHS so add elements from RHS
            arr[k++] = aux[j++];
        }
        else if (j > hi)
        {
            //! True if i <= mid
            //! Processed all elements in RHS so add elements from LHS
            arr[k++] = aux[i++];
        }
        else if (aux[i] <= aux[j])
        {
            //! Can be true if elements remain in LHS and RHS
            //! Element from LHS is smaller than element from RHS
            //! No swapping so no inversions here
            arr[k++] = aux[i++];
        }
        else
        {
            //! Can be true if elements remain in LHS and RHS
            //! Element from LHS is greater than element from RHS
            //! Need to swap, there are inversions
            arr[k++]       = aux[j++];
            num_inversions += mid + 1 - i;
        }
    }

    return num_inversions;

} // long mergeDS( ...

// Test case 0
TEST(CountInversionsTest, TestCase0) {
    EXPECT_EQ(0L, countInversionsFirstAttempt({1, 1, 1, 2, 2}));
    EXPECT_NE(4L, countInversionsFirstAttempt({2, 1, 3, 1, 2}));
    EXPECT_EQ(6L, countInversionsFirstAttempt({2, 1, 3, 1, 2}));
}

// Test case 1
TEST(CountInversionsTest, TestCase1) {
    EXPECT_EQ(1L, countInversionsFirstAttempt({1, 5, 3, 7}));
    EXPECT_NE(6L, countInversionsFirstAttempt({7, 5, 3, 1}));
    EXPECT_EQ(8L, countInversionsFirstAttempt({7, 5, 3, 1}));
}

// Test case 2
TEST(CountInversionsTest, TestCase2) {
    EXPECT_EQ(0L, countInversionsFirstAttempt({1, 3, 5, 7}));
    EXPECT_NE(3L, countInversionsFirstAttempt({3, 2, 1}));
    EXPECT_EQ(5L, countInversionsFirstAttempt({3, 2, 1}));
}