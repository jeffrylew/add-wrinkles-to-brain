#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static std::vector<int> gradingStudents(std::vector<int> grades)
{
    std::transform(grades.begin(),
                   grades.end(),
                   grades.begin(),
                   [](decltype(grades)::value_type grade) -> int {
                       if (grade < 38)
                       {
                           return grade;
                       }
                       
                       int remainder = grade % 10;
                       if (remainder < 3
                           || (remainder > 5 && remainder < 8))
                       {
                           return grade;
                       }
                       
                       if (remainder <= 5)
                       {
                           return (grade - remainder) + 5;
                       }
                       
                       return (grade - remainder) + 10;
                   });
    
    return grades;

} // static std::vector<int> gradingStudents( ...

//! @brief Solution from HR editorial
//! @param[in] grades Vector of grades before rounding
//! @return Vector of grades after rounding
static std::vector<int> gradingStudentsEditorial(std::vector<int> grades)
{
    std::vector<int> output {};

    for (auto i : grades)
    {
        if (i >= 38)
        {
            int j = i;
            while (true)
            {
                if (j % 5 == 0)
                {
                    break;
                }
                ++j;
            }

            if (j - i <= 2)
            {
                i = j;
            }
        }

        output.push_back(i);
    }

    return output;

} // static std::vector<int> gradingStudentsEditorial( ...

//! @brief Solution from HR discussion section
//! @param[in] grades Vector of grades before rounding
//! @return Vector of grades after rounding
static std::vector<int> gradingStudentsDS(std::vector<int> grades)
{
    for (auto& grade : grades)
    {
        if (grade < 38 || grade % 5 <= 2)
        {
            continue;
        }
        else if (grade % 5 > 2)
        {
            grade += 5 - (grade % 5);
        }
    }

    return grades;

} // static std::vector<int> gradingStudentsDS( ...

// Test case 0
TEST(TestGradingStudents, TestCase0) {
    const std::vector<int> expected_output {75, 67, 40, 33};

    const auto result = gradingStudents({73, 67, 38, 33});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));

    const auto result2 = gradingStudentsEditorial({73, 67, 38, 33});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result2.cbegin()));

    const auto result3 = gradingStudentsDS({73, 67, 38, 33});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result3.cbegin()));
}