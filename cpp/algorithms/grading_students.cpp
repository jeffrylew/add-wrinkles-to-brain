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

// Test case 0
TEST(TestGradingStudents, TestCase0) {
    const std::vector<int> expected_output {75, 67, 40, 33};

    const auto result = gradingStudents({73, 67, 38, 33});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}