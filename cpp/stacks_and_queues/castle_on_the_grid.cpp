#include <gtest/gtest.h>

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
    
    //! Minimum number of moves
    int nmoves {};
    
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
            return moves;
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
    
    //! If this point is reached then goal cannot be reached from start
    return 0;

} // static int minimumMovesFA( ...

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