#include <gtest/gtest.h>

#include <cstdio>
#include <sstream>
#include <string>
#include <tuple>

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
    //! @details https://www.hackerrank.com/challenges/time-conversion/forum

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

//! @brief Second solution inspired by HR discussion section
//! @param[in] s std::string containing time in 12 hour format
//! @return std::string containing time in 24 hour format
static std::string timeConversionDS2(std::string s)
{
    //! @details https://www.hackerrank.com/challenges/time-conversion/forum

    int hh {};
    int mm {};
    int ss {};

    std::string t12(3ULL, '\0');

    std::ignore = std::sscanf(s.c_str(), "%d:%d:%d%s", &hh, &mm, &ss, &t12[0]);

    if (t12.substr(0ULL, 2ULL) == "PM" && hh != 12)
    {
        hh += 12;
    }

    if (t12.substr(0ULL, 2ULL) == "AM" && hh == 12)
    {
        hh = 0;
    }
    
    //! Length of output string including null char
    constexpr std::size_t military_t_len {9ULL};
    std::string           output(military_t_len, '\0');

    std::ignore = std::snprintf(&output[0],
                                military_t_len,
                                "%02d:%02d:%02d",
                                hh,
                                mm,
                                ss);
    
    //! Exclude null terminator
    return output.substr(0ULL, military_t_len - 1ULL);

} // static std:string timeConversionDS2( ...

// Test case 0
TEST(TimeConversionTest, TestCase0) {
    EXPECT_EQ("19:05:45", timeConversion("07:05:45PM"));
    EXPECT_EQ("19:05:45", timeConversionDS("07:05:45PM"));
    EXPECT_EQ("19:05:45", timeConversionDS2("07:05:45PM"));
}