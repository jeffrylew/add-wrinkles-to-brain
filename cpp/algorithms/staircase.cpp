#include <gtest/gtest.h>

#include <string>

static std::string staircase(int n)
{
    std::string output {};

    for (int row = 1; row <= n; ++row)
    {
        //! Print space(s)
        for (int nspaces = n - row; nspaces > 0; --nspaces)
        {
            output.append(" ");
        }
        
        //! Print pound(s)
        for (int pounds = row; pounds > 0; --pounds)
        {
            output.append("#");
        }
        
        //! Add newline
        output.append("\n");
    }

    return output;

} // static std::string staircase(int n)

// Test case 1
TEST(StaircaseTest, TestCase1) {
    const std::string expected {
        "     #\n    ##\n   ###\n  ####\n #####\n######\n"};

    EXPECT_EQ(expected, staircase(6));
}