#include <gtest/gtest.h>

#include <string>

//! @brief First attempt solution for if kangaroos can reach same location
//! @param[in] x1 Starting location of first kangaroo
//! @param[in] v1 Distance covered per jump of first kangaroo
//! @param[in] x2 Starting location of second kangaroo
//! @param[in] v2 Distance covered per jump of second kangaroo
//! @return "YES" if both kangaroos can reach same location, else no
static std::string kangarooFA(int x1, int v1, int x2, int v2)
{
    //! @details First attempt solution passes Test cases 0-2, 5-7, 10-11, 14,
    //!          16, 18, 21, 24-27, 29

    const bool never_intersect {(x1 >= x2 && v1 > v2)
                               || (x1 > x2 && v1 == v2)
                               || (x1 <= x2 && v1 < v2)
                               || (x1 < x2 && v1 == v2)};
    
    return not never_intersect ? "YES" : "NO";
}

// Test case 0
TEST(KangarooTest, TestCase0) {
    EXPECT_EQ("YES", kangarooFA(0, 3, 4, 2));
}

// Test case 1
TEST(KangarooTest, TestCase1) {
    EXPECT_EQ("NO", kangarooFA(0, 2, 5, 3));
}
