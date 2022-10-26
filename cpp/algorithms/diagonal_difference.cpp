#include <gtest/gtest.h>

#include <cmath>
#include <vector>

//! @brief Calculate abs diff between sums of its diagonals
//! @param[in] arr 2D vector of integers
//! @return The absolute diagonal difference
static int diagonalDifference(std::vector<std::vector<int>> arr)
{
    const auto arr_size = static_cast<int>(arr.size());
    
    //! Evaluate left-to-right and right-to-left diagonals
    int col {arr_size};
    int ltr_diagonal {};
    int rtl_diagonal {};
    for (int i = 0; i < arr_size; ++i)
    {
        ltr_diagonal += arr[i][i];
        rtl_diagonal += arr[i][--col];
    }
    
    return std::abs(ltr_diagonal - rtl_diagonal);

} // static int diagonalDifference( ...

//! @brief Solution from HR discussion section
//! @param[in] arr 2D vector of integers
//! @return The absolute diagonal difference
static int diagonalDifferenceDS(std::vector<std::vector<int>> arr)
{
    //! Square matrix
    const auto arr_size = static_cast<int>(arr.size());

    int leftD {};
    int rightD {};

    for (int j = 0; j < arr_size; ++j)
    {
        for (int i = 0; i < arr_size; ++i)
        {
            if (j == i)
            {
                leftD += arr[j][i];
            }
            if (j + i == (arr_size - 1))
            {
                rightD += arr[j][i];
            }
        }
    }
    
    return std::abs(leftD - rightD);

} // static int diagonalDifferenceDS( ...

// Test case 0
TEST(DiagonalDifferenceTest, TestCase0) {
    EXPECT_EQ(15, diagonalDifference({{11, 2, 4}, {4, 5, 6}, {10, 8, -12}}));
    EXPECT_EQ(15, diagonalDifferenceDS({{11, 2, 4}, {4, 5, 6}, {10, 8, -12}}));
}