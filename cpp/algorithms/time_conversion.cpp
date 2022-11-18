#include <gtest/gtest.h>

#include <sstream>
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

//! @brief Solution inspired by HR discussion section
//! @param[in] s std::string containing time in 12 hour format
//! @return std::string containing time in 24 hour format
static std::string timeConversionDS(std::string s)
{
    std::stringstream ss {s};
    std::string       ele {};

    std::getline(ss, ele, ':');
    int hr {std::stoi(ele)};

    hr = (s[8] == 'A') ? (hr == 12 ? 0 : hr) : (hr == 12 ? 12 : hr + 12);

    ss.str("");
    ss.clear();
    ss.fill('0');
    ss.width(2);
    ss << hr;

    return ss.str() + s.substr(2ULL, 6ULL);

} // static std::string timeConversionDS( ...

// Test case 0
TEST(TimeConversionTest, TestCase0) {
    EXPECT_EQ("19:05:45", timeConversion("07:05:45PM"));
    EXPECT_EQ("19:05:45", timeConversionDS("07:05:45PM"));
}