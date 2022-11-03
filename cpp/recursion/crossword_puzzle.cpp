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

//! @brief Populate vecs_ref from crossword
//! @param[in,out] crossword Reference to vector of 10 strings
//! @param[out]    vecs_ref  Reference to Vecs_ref_t
static void populate_refs(std::vector<std::string>& crossword,
                          Vecs_ref_t&               vecs_ref)
{
    //! Vector of words in rows
    auto& row_words = std::get<0>(vecs_ref);
    
    //! Vector of words in cols
    auto& col_words = std::get<1>(vecs_ref);
    
    //! Populate row_words
    for (int row = 0; row < crossword.size(); ++row)
    {
        //! Flag to keep track if a new word has been found in the row
        bool new_word_in_row {};

        for (int col = 0; col < crossword.front().size(); ++col)
        {
            if ('-' != crossword[row][col])
            {
                new_word_in_row = false;
                continue;
            }

            if (not new_word_in_row)
            {
                //! The first time hyphen is encountered, create new vector
                //! containing crossword[row][col]. Set new_word_in_row to true
                row_words.emplace_back({crossword[row][col]});
                new_word_in_row = true;
            }
            else
            {
                //! Found hyphen but already created new vector
                //! Just append hyphen to existing vector
                row_words.back().emplace_back(crossword[row][col]);
            }
            
        } // for (int col = 0; ...

    } // for (int row = 0; ...

    //! @todo Populate col_words

} // static Vecs_ref_t populate_refs( ...

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

