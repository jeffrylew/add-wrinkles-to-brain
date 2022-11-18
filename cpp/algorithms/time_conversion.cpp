#include <gtest/gtest.h>

#include <string>

static std::string timeConversion(std::string s)
{
    const bool is_am {s.substr(8ULL) == "AM"};
    const auto hours_str {s.substr(0ULL, 2ULL)};
    
    if (is_am)
    {
        if (hours_str == "12")
        {
            return "00" + s.substr(2ULL, 6ULL);
        }
        return s.substr(0ULL, 8ULL);
    }
    else
    {
        if (hours_str == "12")
        {
            return s.substr(0ULL, 8ULL);
        }
        
        const int hours {std::stoi(hours_str)};
        return std::to_string(hours + 12) + s.substr(2ULL, 6ULL);
    }

} // static std::string timeConversion( ...

// Test case 0
TEST(TimeConversionTest, TestCase0) {
    EXPECT_EQ("19:05:45", timeConversion("07:05:45PM"));
}