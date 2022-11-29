#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

//! @brief First attempt solution passes test cases 5, 7, 10-13
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

    //! Set of already processed coords
    std::set<std::pair<int, int>> processed_coords {};
    std::ignore = processed_coords.emplace(startX, startY);

    //! Keep track of minimum moves for all valid paths from start to goal
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
    int min_moves {std::numeric_limits<int>::max()};
    
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
            //! Found a valid path from start to goal, can update min_moves
            if (moves < min_moves)
            {
                min_moves = moves;
            }
            continue;
        }
    
        //! Add valid adjacent col (Y) coordinates if not 'X'
        if (col - 1 >= 0
            && grid[row][col - 1] != 'X'
            && 0 == processed_coords.count({row, col - 1}))
        {
            unexplored_coords.emplace(row,
                                      col - 1,
                                      Dir::travel_row,
                                      dir == Dir::travel_row ? moves
                                                             : moves + 1);
            std::ignore = processed_coords.emplace(row, col - 1);
        }
        if (col + 1 < ncols
            && grid[row][col + 1] != 'X'
            && 0 == processed_coords.count({row, col + 1}))
        {
            unexplored_coords.emplace(row,
                                      col + 1,
                                      Dir::travel_row,
                                      dir == Dir::travel_row ? moves
                                                             : moves + 1);
            std::ignore = processed_coords.emplace(row, col + 1);
        }
        
        //! Add valid adjacent row (X) coordinates if not 'X'
        if (row - 1 >= 0
            && grid[row - 1][col] != 'X'
            && 0 == processed_coords.count({row - 1, col}))
        {
            unexplored_coords.emplace(row - 1,
                                      col,
                                      Dir::travel_col,
                                      dir == Dir::travel_col ? moves
                                                             : moves + 1);
            std::ignore = processed_coords.emplace(row - 1, col);
        }
        if (row + 1 < nrows
            && grid[row + 1][col] != 'X'
            && 0 == processed_coords.count({row + 1, col}))
        {
            unexplored_coords.emplace(row + 1,
                                      col,
                                      Dir::travel_col,
                                      dir == Dir::travel_col ? moves
                                                             : moves + 1);
            std::ignore = processed_coords.emplace(row + 1, col);
        }
        
    } // while (not unexplored_coords.empty())
    
    //! If min_moves is max int then goal cannot be reached from start
    return min_moves == std::numeric_limits<int>::max() ? 0 : min_moves;

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