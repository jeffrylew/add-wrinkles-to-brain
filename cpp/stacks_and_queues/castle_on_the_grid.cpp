#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

//! @brief First attempt solution passes test cases 10, 12, 13
//! @param[in] grid   Vector of strings representing rows of grid
//! @param[in] startX Starting X coordinate
//! @param[in] startY Starting Y coordinate
//! @param[in] goalX  Ending X coordinate
//! @param[in] goalY  Ending Y coordinate
//! @return Minimum moves to reach the goal
static int minimumMovesFA(std::vector<std::string> grid,
                          int                      startX,
                          int                      startY,
                          int                      goalX,
                          int                      goalY)
{
    //! Enum indicating if at start coord, traveling along row,
    //! or traveling along col
    enum class Dir
    {
        start,
        travel_row,
        travel_col
    };
    
    //! Queue of coords/data <row, col, Dir, moves> to process
    std::queue<std::tuple<int, int, Dir, int>> unexplored_coords {};
    unexplored_coords.emplace(startX, startY, Dir::start, 0);
    
    //! Number of moves along current path
    int nmoves {};

    //! Keep track of moves for all valid paths from start to goal
    //! Need this since breadth first search finds the shortest path in terms
    //! of row/col increments but there may be another path with the same
    //! number of increments but have fewer "moves" as the problem describes.
    //! e.g. Start coord at "s" and goal coord at "e"
    //!     ". . . ."
    //!     "s . X e"
    //! Valid paths (denoted by "p") with same row/increments (6 "p" chars) are
    //!     "p p p p"        and        "  p p p"
    //!     "p   X p"                   "p p X p"
    //! but the path on the left has 3 moves whereas the right has 4 moves
    std::vector<int> valid_moves {};
    
    //! Grid extents
    const auto nrows = static_cast<int>(grid.size());
    const auto ncols = static_cast<int>(grid.front().size());
    
    while (not unexplored_coords.empty())
    {
        const auto data = unexplored_coords.front();
        unexplored_coords.pop();
        
        //! Current coordinate/direction/number of moves
        const auto row   = std::get<0>(data);
        const auto col   = std::get<1>(data);
        const auto dir   = std::get<2>(data);
        const auto moves = std::get<3>(data);
        
        if (row == goalX && col == goalY)
        {
            //! Found a valid path from start to goal, save its number of moves
            valid_moves.push_back(moves);
            continue;
        }
    
        //! Add valid adjacent col (Y) coordinates if not 'X'
        if (col - 1 >= 0 && grid[row][col - 1] != 'X')
        {
            if (dir != Dir::travel_row)
            {
                nmoves = moves + 1;
            }
            unexplored_coords.emplace(row, col - 1, Dir::travel_row, nmoves);
        }
        if (col + 1 < ncols && grid[row][col + 1] != 'X')
        {
            if (dir != Dir::travel_row)
            {
                nmoves = moves + 1;
            }
            unexplored_coords.emplace(row, col + 1, Dir::travel_row, nmoves);
        }
        
        //! Add valid adjacent row (X) coordinates if not 'X'
        if (row - 1 >= 0 && grid[row - 1][col] != 'X')
        {
            if (dir != Dir::travel_col)
            {
                nmoves = moves + 1;
            }
            unexplored_coords.emplace(row - 1, col, Dir::travel_col, nmoves);
        }
        if (row + 1 < nrows && grid[row + 1][col] != 'X')
        {
            if (dir != Dir::travel_col)
            {
                nmoves = moves + 1;
            }
            unexplored_coords.emplace(row + 1, col, Dir::travel_col, nmoves);
        }
        
    } // while (not unexplored_coords.empty())
    
    //! If valid_moves is empty then goal cannot be reached from start
    return valid_moves.empty() ? 0 : *std::min_element(valid_moves.cbegin(),
                                                       valid_moves.cend());

} // static int minimumMovesFA( ...

// Test case 0
TEST(MinimumMovesTest, TestCase0) {
    EXPECT_EQ(3, minimumMovesFA({".X..XX...X",
                                 "X.........",
                                 ".X.......X",
                                 "..........",
                                 "........X.",
                                 ".X...XXX..",
                                 ".....X..XX",
                                 ".....X.X..",
                                 "..........",
                                 ".....X..XX"},
                                 9,
                                 1,
                                 9,
                                 6));
}

// Test case 10
TEST(MinimumMovesTest, TestCase10) {
    EXPECT_EQ(3, minimumMovesFA({".X.", ".X.", "..."}, 0, 0, 0, 2));
}

// Test case 12
TEST(MinimumMovesTest, TestCase12) {
    EXPECT_EQ(2, minimumMovesFA({"...", ".X.", ".X."}, 2, 0, 0, 2));
}

// Test case 13
TEST(MinimumMovesTest, TestCase13) {
    EXPECT_EQ(3, minimumMovesFA({"...", ".X.", ".X."}, 2, 0, 2, 2));
}