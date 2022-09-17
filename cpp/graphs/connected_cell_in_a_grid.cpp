#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

//! @brief First attempt solution passes all test cases but needs refactoring
//! @param[in] grid Two dimensional grid of integers
//! @return Size of largest region
static int maxRegionFirstAttempt(std::vector<std::vector<int>> grid)
{
    //! Keep track of number of connected cells in each region
    std::vector<int> cells_per_region {};
    
    //! Keep track of filled cells that have been processed
    std::set<std::pair<int, int>> filled_cells {};
    
    //! Queue of filled cells to check neighbors of
    std::queue<std::pair<int, int>> connected_cells_todo {};
    
    //! Define constants for row and col sizes
    const auto n_rows = static_cast<int>(grid.size());
    const auto n_cols = static_cast<int>(grid.front().size());
    
    //! Find initial filled cell that is seed for region
    for (int seed_row = 0; seed_row < n_rows; ++seed_row)
    {
        for (int seed_col = 0; seed_col < n_cols; ++seed_col)
        {
            if (0 == grid[seed_row][seed_col])
            {
                //! Not a filled cell, skip
                continue;
            }
            
            if (not filled_cells.emplace(seed_row, seed_col).second)
            {
                //! Filled cell was already processed, skip
                continue;
            }
            
            //! Initialize new region with number of cells = 1
            cells_per_region.emplace_back(1);
            
            //! Add seed cell for region to queue
            connected_cells_todo.emplace(seed_row, seed_col);
            
            //! Now search its neighbors
            while (not connected_cells_todo.empty())
            {
                const auto curr_cell = connected_cells_todo.front();
                const auto row       = curr_cell.first;
                const auto col       = curr_cell.second;
                connected_cells_todo.pop();
                
                //! Add filled neighbors 
                if (0 == row && 0 == col)
                {
                    //! Top left corner
                    if (row + 1 < n_rows
                        && 1 == grid[row + 1][col]
                        && filled_cells.emplace(row + 1, col).second)
                    {
                        connected_cells_todo.emplace(row + 1, col);
                        ++cells_per_region.back();
                    }
                    if (col + 1 < n_cols
                        && 1 == grid[row][col + 1]
                        && filled_cells.emplace(row, col + 1).second)
                    {
                        connected_cells_todo.emplace(row, col + 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col + 1 < n_cols
                        && 1 == grid[row + 1][col + 1]
                        && filled_cells.emplace(row + 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col + 1);
                        ++cells_per_region.back();
                    }
                }
                else if (0 == row && n_cols - 1 == col)
                {
                    //! Top right corner
                    if (col - 1 >= 0
                        && 1 == grid[row][col - 1]
                        && filled_cells.emplace(row, col - 1).second)
                    {
                        connected_cells_todo.emplace(row, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col - 1 >= 0
                        && 1 == grid[row + 1][col - 1]
                        && filled_cells.emplace(row + 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && 1 == grid[row + 1][col]
                        && filled_cells.emplace(row + 1, col).second)
                    {
                        connected_cells_todo.emplace(row + 1, col);
                        ++cells_per_region.back();
                    }
                }
                else if (n_rows - 1 == row && 0 == col)
                {
                    //! Bottom left corner
                    /*
                    if (row - 1 >= 0
                        && 1 == grid[row - 1][col]
                        && filled_cells.emplace(row - 1, col).second)
                    {
                        connected_cells_todo.emplace(row - 1, col);
                        ++cells_per_region.back();
                    }
                    if (row - 1 >= 0
                        && col + 1 < n_cols
                        && 1 == grid[row - 1][col + 1]
                        && filled_cells.emplace(row - 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col + 1);
                        ++cells_per_region.back();
                    }
                    */
                    if (col + 1 < n_cols
                        && 1 == grid[row][col + 1]
                        && filled_cells.emplace(row, col + 1).second)
                    {
                        connected_cells_todo.emplace(row, col + 1);
                        ++cells_per_region.back();
                    }
                }
                else if (n_rows - 1 == row && n_cols - 1 == col)
                {
                    //! Bottom right corner
                    /*
                    if (row - 1 >= 0
                        && col - 1 >= 0
                        && 1 == grid[row - 1][col - 1]
                        && filled_cells.emplace(row - 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row - 1 >= 0
                        && 1 == grid[row - 1][col]
                        && filled_cells.emplace(row - 1, col).second)
                    {
                        connected_cells_todo.emplace(row - 1, col);
                        ++cells_per_region.back();
                    }
                    */
                    
                    //! Technically this isn't needed either,
                    //! Any filled cell surrounding the bottom right
                    //! corner would have already been processed
                    if (col - 1 >= 0
                        && 1 == grid[row][col - 1]
                        && filled_cells.emplace(row, col - 1).second)
                    {
                        connected_cells_todo.emplace(row, col - 1);
                        ++cells_per_region.back();
                    }
                }
                else if (0 == row)
                {
                    //! Top edge
                    if (col - 1 >= 0
                        && 1 == grid[row][col - 1]
                        && filled_cells.emplace(row, col - 1).second)
                    {
                        connected_cells_todo.emplace(row, col - 1);
                        ++cells_per_region.back();
                    }
                    if (col + 1 < n_cols
                        && 1 == grid[row][col + 1]
                        && filled_cells.emplace(row, col + 1).second)
                    {
                        connected_cells_todo.emplace(row, col + 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col - 1 >= 0
                        && 1 == grid[row + 1][col - 1]
                        && filled_cells.emplace(row + 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && 1 == grid[row + 1][col]
                        && filled_cells.emplace(row + 1, col).second)
                    {
                        connected_cells_todo.emplace(row + 1, col);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col + 1 < n_cols
                        && 1 == grid[row + 1][col + 1]
                        && filled_cells.emplace(row + 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col + 1);
                        ++cells_per_region.back();
                    }
                }
                else if (0 == col)
                {
                    //! Left edge
                    /*
                    if (row - 1 >= 0
                        && 1 == grid[row - 1][col]
                        && filled_cells.emplace(row - 1, col).second)
                    {
                        connected_cells_todo.emplace(row - 1, col);
                        ++cells_per_region.back();
                    }
                    if (row - 1 >= 0
                        && col + 1 < n_cols
                        && 1 == grid[row - 1][col + 1]
                        && filled_cells.emplace(row - 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col + 1);
                        ++cells_per_region.back();
                    }
                    */
                    if (col + 1 < n_cols
                        && 1 == grid[row][col + 1]
                        && filled_cells.emplace(row, col + 1).second)
                    {
                        connected_cells_todo.emplace(row, col + 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && 1 == grid[row + 1][col]
                        && filled_cells.emplace(row + 1, col).second)
                    {
                        connected_cells_todo.emplace(row + 1, col);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col + 1 < n_cols
                        && 1 == grid[row + 1][col + 1]
                        && filled_cells.emplace(row + 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col + 1);
                        ++cells_per_region.back();
                    }
                }
                else if (grid.size() - 1 == row)
                {
                    //! Bottom edge
                    /*
                    if (row - 1 >= 0
                        && col - 1 >= 0
                        && 1 == grid[row - 1][col - 1]
                        && filled_cells.emplace(row - 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row - 1 >= 0
                        && 1 == grid[row - 1][col]
                        && filled_cells.emplace(row - 1, col).second)
                    {
                        connected_cells_todo.emplace(row - 1, col);
                        ++cells_per_region.back();
                    }
                    */
                    
                    //! Even though row - 1 here, need to keep since col + 1
                    if (row - 1 >= 0
                        && col + 1 < n_cols
                        && 1 == grid[row - 1][col + 1]
                        && filled_cells.emplace(row - 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col + 1);
                        ++cells_per_region.back();
                    }
                    if (col - 1 >= 0
                        && 1 == grid[row][col - 1]
                        && filled_cells.emplace(row, col - 1).second)
                    {
                        connected_cells_todo.emplace(row, col - 1);
                        ++cells_per_region.back();
                    }
                    if (col + 1 < n_cols
                        && 1 == grid[row][col + 1]
                        && filled_cells.emplace(row, col + 1).second)
                    {
                        connected_cells_todo.emplace(row, col + 1);
                        ++cells_per_region.back();
                    }
                }
                else if (grid.front().size() - 1 == col)
                {
                    //! Right edge
                    /*
                    if (row - 1 >= 0
                        && 1 == grid[row - 1][col]
                        && filled_cells.emplace(row - 1, col).second)
                    {
                        connected_cells_todo.emplace(row - 1, col);
                        ++cells_per_region.back();
                    }
                    if (row - 1 >= 0
                        && col - 1 >= 0
                        && 1 == grid[row - 1][col - 1]
                        && filled_cells.emplace(row - 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col - 1);
                        ++cells_per_region.back();
                    }
                    */
                    if (col - 1 >= 0
                        && 1 == grid[row][col - 1]
                        && filled_cells.emplace(row, col - 1).second)
                    {
                        connected_cells_todo.emplace(row, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col - 1 >= 0
                        && 1 == grid[row + 1][col - 1]
                        && filled_cells.emplace(row + 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && 1 == grid[row + 1][col]
                        && filled_cells.emplace(row + 1, col).second)
                    {
                        connected_cells_todo.emplace(row + 1, col);
                        ++cells_per_region.back();
                    }
                }
                else
                {
                    // row > 0 && col > 0
                    /*
                    if (row - 1 >= 0
                        && col - 1 >= 0
                        && 1 == grid[row - 1][col - 1]
                        && filled_cells.emplace(row - 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row - 1 >= 0
                        && 1 == grid[row - 1][col]
                        && filled_cells.emplace(row - 1, col).second)
                    {
                        connected_cells_todo.emplace(row - 1, col);
                        ++cells_per_region.back();
                    }
                    */
                    
                    //! Even though row - 1 here, need to keep since col + 1
                    if (row - 1 >= 0
                        && col + 1 < n_cols
                        && 1 == grid[row - 1][col + 1]
                        && filled_cells.emplace(row - 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row - 1, col + 1);
                        ++cells_per_region.back();
                    }
                    if (col - 1 >= 0
                        && 1 == grid[row][col - 1]
                        && filled_cells.emplace(row, col - 1).second)
                    {
                        connected_cells_todo.emplace(row, col - 1);
                        ++cells_per_region.back();
                    }
                    if (col + 1 < n_cols
                        && 1 == grid[row][col + 1]
                        && filled_cells.emplace(row, col + 1).second)
                    {
                        connected_cells_todo.emplace(row, col + 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col - 1 >= 0
                        && 1 == grid[row + 1][col - 1]
                        && filled_cells.emplace(row + 1, col - 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col - 1);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && 1 == grid[row + 1][col]
                        && filled_cells.emplace(row + 1, col).second)
                    {
                        connected_cells_todo.emplace(row + 1, col);
                        ++cells_per_region.back();
                    }
                    if (row + 1 < n_rows
                        && col + 1 < n_cols
                        && 1 == grid[row + 1][col + 1]
                        && filled_cells.emplace(row + 1, col + 1).second)
                    {
                        connected_cells_todo.emplace(row + 1, col + 1);
                        ++cells_per_region.back();
                    }
                    
                } // else -> if (0 == row && 0 == col)
                
            } // while (not connected_cells_todo.empty())
            
        } // for (int seed_col = 0; ...
        
    } // for (int seed_row = 0; ...
    
    return cells_per_region.empty()
        ? 0
        : *std::max_element(cells_per_region.cbegin(), cells_per_region.cend());

} // static int maxRegionFirstAttempt( ...

// Test case 0
TEST(MaxRegionTest, TestCase0) {
    const std::vector<std::vector<int>> grid {{1, 1, 0, 0},
                                              {0, 1, 1, 0},
                                              {0, 0, 1, 0},
                                              {1, 0, 0, 0}};
    
    EXPECT_EQ(5, maxRegionFirstAttempt(grid));
}

// Test case 1
TEST(MaxRegionTest, TestCase1) {
    const std::vector<std::vector<int>> grid {{0, 0, 1, 1},
                                              {0, 0, 1, 0},
                                              {0, 1, 1, 0},
                                              {0, 1, 0, 0},
                                              {1, 1, 0, 0}};
    
    EXPECT_EQ(8, maxRegionFirstAttempt(grid));
}

// Test case 7
TEST(MaxRegionTest, TestCase7) {
    const std::vector<std::vector<int>> grid {{1, 0, 1, 1, 0},
                                              {1, 1, 0, 0, 1},
                                              {0, 1, 1, 1, 0},
                                              {0, 0, 0, 0, 1},
                                              {1, 1, 1, 0, 0}};
    
    EXPECT_EQ(10, maxRegionFirstAttempt(grid));
}