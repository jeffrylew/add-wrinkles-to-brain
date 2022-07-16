#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <vector>

static int hourglassSum(std::vector<std::vector<int>> arr)
{
    std::array<int, 16> sums {};
    
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        const auto& row = arr.at(i);
        
        if (row.size() < 6ULL)
        {
            continue;
        }
        
        switch (i)
        {
            case 0:
                sums.at(0) += row.at(0) + row.at(1) + row.at(2);
                sums.at(1) += row.at(1) + row.at(2) + row.at(3);
                sums.at(2) += row.at(2) + row.at(3) + row.at(4);
                sums.at(3) += row.at(3) + row.at(4) + row.at(5);
                break;
            case 1:
                sums.at(0) += row.at(1);
                sums.at(1) += row.at(2);
                sums.at(2) += row.at(3);
                sums.at(3) += row.at(4);
                sums.at(4) += row.at(0) + row.at(1) + row.at(2);
                sums.at(5) += row.at(1) + row.at(2) + row.at(3);
                sums.at(6) += row.at(2) + row.at(3) + row.at(4);
                sums.at(7) += row.at(3) + row.at(4) + row.at(5);
                break;
            case 2:
                sums.at(0)  += row.at(0) + row.at(1) + row.at(2);
                sums.at(1)  += row.at(1) + row.at(2) + row.at(3);
                sums.at(2)  += row.at(2) + row.at(3) + row.at(4);
                sums.at(3)  += row.at(3) + row.at(4) + row.at(5);
                sums.at(4)  += row.at(1);
                sums.at(5)  += row.at(2);
                sums.at(6)  += row.at(3);
                sums.at(7)  += row.at(4);
                sums.at(8)  += row.at(0) + row.at(1) + row.at(2);
                sums.at(9)  += row.at(1) + row.at(2) + row.at(3);
                sums.at(10) += row.at(2) + row.at(3) + row.at(4);
                sums.at(11) += row.at(3) + row.at(4) + row.at(5);
                break;
            case 3:
                sums.at(4)  += row.at(0) + row.at(1) + row.at(2);
                sums.at(5)  += row.at(1) + row.at(2) + row.at(3);
                sums.at(6)  += row.at(2) + row.at(3) + row.at(4);
                sums.at(7)  += row.at(3) + row.at(4) + row.at(5);
                sums.at(8)  += row.at(1);
                sums.at(9)  += row.at(2);
                sums.at(10) += row.at(3);
                sums.at(11) += row.at(4);
                sums.at(12) += row.at(0) + row.at(1) + row.at(2);
                sums.at(13) += row.at(1) + row.at(2) + row.at(3);
                sums.at(14) += row.at(2) + row.at(3) + row.at(4);
                sums.at(15) += row.at(3) + row.at(4) + row.at(5);
                break;
            case 4:
                sums.at(8)  += row.at(0) + row.at(1) + row.at(2);
                sums.at(9)  += row.at(1) + row.at(2) + row.at(3);
                sums.at(10) += row.at(2) + row.at(3) + row.at(4);
                sums.at(11) += row.at(3) + row.at(4) + row.at(5);
                sums.at(12) += row.at(1);
                sums.at(13) += row.at(2);
                sums.at(14) += row.at(3);
                sums.at(15) += row.at(4);
                break;
            case 5:
                sums.at(12) += row.at(0) + row.at(1) + row.at(2);
                sums.at(13) += row.at(1) + row.at(2) + row.at(3);
                sums.at(14) += row.at(2) + row.at(3) + row.at(4);
                sums.at(15) += row.at(3) + row.at(4) + row.at(5);
                break;
                
        } // switch (i) ...
        
    } // for (std::size_t i = 0; i < arr.size(); ++i)
    
    const auto max_it = std::max_element(sums.cbegin(), sums.cend());
    return max_it == sums.cend() ? 0 : *max_it;

} // static int hourglassSum( ...

// Test case 0
TEST(HourglassSumTest, TestCase0) {
    EXPECT_EQ(19, hourglassSum({{1, 1, 1, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {1, 1, 1, 0, 0, 0},
                                {0, 0, 2, 4, 4, 0},
                                {0, 0, 0, 2, 0, 0},
                                {0, 0, 1, 2, 4, 0}}));
}

// Test case 1
TEST(HourglassSumTest, TestCase1) {
    EXPECT_EQ(13, hourglassSum({{1, 1, 1, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {1, 1, 1, 0, 0, 0},
                                {0, 9, 2, -4, -4, 0},
                                {0, 0, 0, -2, 0, 0},
                                {0, 0, -1, -2, -4, 0}}));
}

// Test case 8
TEST(HourglassSumTest, TestCase8) {
    EXPECT_EQ(28, hourglassSum({{-9, -9, -9, 1, 1, 1},
                                {0, -9, 0, 4, 3, 2},
                                {-9, -9, -9, 1, 2, 3},
                                {0, 0, 8, 6, 6, 0},
                                {0, 0, 0, -2, 0, 0},
                                {0, 0, 1, 2, 4, 0}}));
}
