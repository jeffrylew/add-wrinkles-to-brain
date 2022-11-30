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

//! @brief Helper function to increment the number of moves at given position
//! @param[in,out] nmoves     Reference to 2D vector of moves at each position
//! @param[in]     row        Row/X index of position
//! @param[in]     col        Column/Y index of position
//! @param[in]     curr_moves Current number of moves at position
static void addStep(std::vector<std::vector<int>>& nmoves,
                    int                            row,
                    int                            col,
                    int                            curr_moves)
{
    //! nmoves is initialized to 100 at each non-'X' position, which is the max
    //! number of moves as specified in the problem description
    if (nmoves[row][col] > curr_moves + 1)
    {
        nmoves[row][col] = curr_moves + 1;
    }
    
} // static void addStep( ...

//! @brief Helper function to generate positions to process and update nmoves
//! @param[in]     coord      Reference to current position as pair<row, col>
//! @param[in,out] nmoves     Reference to 2D vector of moves at each position
//! @param[in,out] to_process Reference to queue of positions to process
static void moveGenerator(const std::pair<int, int>&       coord,
                          std::vector<std::vector<int>>&   nmoves,
                          std::queue<std::pair<int, int>>& to_process)
{
    auto n          = static_cast<int>(nmoves.size());
    auto row        = coord.first;
    auto col        = coord.second;
    auto curr_moves = nmoves[row][col];

    //! Travel down rows (south) at fixed col until 'X' is reached
    //! Seems like initial position at row,col is processed more than once
    //! although the pos_visited grid in minimumMovesDS skips the processing
    //! The cell at row + 1,col will have its number of moves incremented along
    //! with all the ones below until 'X' is reached
    for (int i = row; i < n && nmoves[i][col] != -1; ++i)
    {
        addStep(nmoves, i, col, curr_moves);
        to_process.emplace(i, col);
    }
    
    //! Travel up rows (north) at fixed col until 'X' is reached
    for (int i = row; i >= 0 && nmoves[i][col] != -1; --i)
    {
        addStep(nmoves, i, col, curr_moves);
        to_process.emplace(i, col);
    }

    //! Travel right across cols (east) at fixed row until 'X' is reached
    for (int i = col; i < n && nmoves[row][i] != -1; ++i)
    {
        addStep(nmoves, row, i, curr_moves);
        to_process.emplace(row, i);
    }

    //! Travel left across cols (west) at fixed row until 'X' is reached
    for (int i = col; i >= 0 && nmoves[row][i] != -1; --i)
    {
        addStep(nmoves, row, i, curr_moves);
        to_process.emplace(row, i);
    }

} // static void moveGenerator( ...

//! @brief Solution from HR discussion section
//! @param[in] grid   Vector of strings representing rows of grid
//! @param[in] startX Starting X coordinate
//! @param[in] startY Starting Y coordinate
//! @param[in] goalX  Ending X coordinate
//! @param[in] goalY  Ending Y coordinate
//! @return Minimum moves to reach the goal
static int minimumMovesDS(std::vector<std::string> grid,
                          int                      startX,
                          int                      startY,
                          int                      goalX,
                          int                      goalY)
{
    //! @details https://www.hackerrank.com/challenges/castle-on-the-grid/forum
    //!
    //!          Idea is to fill all positions in grid with number of moves it
    //!          takes to reach each position. Use a helper grid of same size
    //!          to store if position has been visited and use a queue to store
    //!          the next move

    const auto grid_size = grid.size();
    const auto n         = static_cast<int>(grid_size);

    //! Number of moves at each position
    std::vector<std::vector<int>> nmoves(grid_size,
                                         std::vector<int>(grid_size));
    
    //! Initialize nmoves
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            nmoves[row][col] = (grid[row][col] == '.') ? 100 : -1;
        }
    }
    nmoves[startX][startY] = 0;

    //! Helper grid storing if position has been visited
    std::vector<std::vector<bool>> pos_visited(grid_size,
                                               std::vector<bool>(grid_size));
    
    //! Queue storing next moves <row/X, col/Y>
    std::queue<std::pair<int, int>> unexplored_coords {};
    unexplored_coords.emplace(startX, startY);
    
    while (not unexplored_coords.empty())
    {
        const auto pos = unexplored_coords.front();
        unexplored_coords.pop();

        if (not pos_visited[pos.first][pos.second])
        {
            pos_visited[pos.first][pos.second] = true;

            moveGenerator(pos, nmoves, unexplored_coords);
        }
    }
    
    return nmoves[goalX][goalY];

} // static int minimumMovesDS( ...

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

    EXPECT_EQ(3, minimumMovesDS({".X..XX...X",
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

    EXPECT_EQ(3, minimumMovesDS({".X.", ".X.", "..."}, 0, 0, 0, 2));
}

// Test case 12
TEST(MinimumMovesTest, TestCase12) {
    EXPECT_EQ(2, minimumMovesFA({"...", ".X.", ".X."}, 2, 0, 0, 2));

    EXPECT_EQ(2, minimumMovesDS({"...", ".X.", ".X."}, 2, 0, 0, 2));
}

// Test case 13
TEST(MinimumMovesTest, TestCase13) {
    EXPECT_EQ(3, minimumMovesFA({"...", ".X.", ".X."}, 2, 0, 2, 2));

    EXPECT_EQ(3, minimumMovesDS({"...", ".X.", ".X."}, 2, 0, 2, 2));
}