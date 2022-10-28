#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

//! Type alias for 2D vectors for horizontal and vertical words
using Vecs_ref_t = std::tuple<std::vector<std::vector<char&>>,
                              std::vector<std::vector<char&>>>;

//! @brief Tokenize input string into vector
//! @param[in] input String to split
//! @param[in] delim Character delimiter
//! @return Vector of tokenized strings
static std::vector<std::string> split(std::string input, char delim)
{
    //! @details https://stackoverflow.com/questions/14265581/
    //!          parse-split-a-string-in-c-using-string-delimiter-standard-c

    std::vector<std::string> output {};
    std::istringstream       isstream {input};
    std::string              item;

    while (std::getline(isstream, item, delim))
    {
        output.push_back(item);
    }

    return output;

} // static std::vector<std::string> split( ...

//! @brief Reset 2D vector of char refs to crossword to contain original '-'
//! @param[out] tuple_vecs Reference to Vecs_ref_t
static void reset(Vecs_ref_t& tuple_vecs)
{
    auto& horiz_words = std::get<0>(tuple_vecs);
    auto& vert_words  = std::get<1>(tuple_vecs);

    for (auto& char_vec : horiz_words)
    {
        std::fill(char_vec.begin(), char_vec.end(), '-');
    }

    for (auto& char_vec : vert_words)
    {
        std::fill(char_vec.begin(), char_vec.end(), '-');
    }
}

//! @brief First attempt solution
static std::vector<std::string> crosswordPuzzleFirstAttempt(
    std::vector<std::string> crossword,
    std::string              words)
{

} // std::vector<std::string> crosswordPuzzleFirstAttempt( ...

// Test case X
TEST(CrosswordPuzzleTest, TestCaseX) {

}

// Test case Y
TEST(CrosswordPuzzleTest, TestCaseY) {

}

