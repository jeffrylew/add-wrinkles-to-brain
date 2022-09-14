#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

//! @brief First attempt solution passes all tests
//! @param[in] graph_nodes Number of nodes
//! @param[in] graph_from  Vector of start nodes for each edge
//! @param[in] graph_to    Vector of end nodes for each edge
//! @param[in] ids         Color id per node
//! @param[in] val         Color id to match
//! @return Length of shortest path between two nodes of same color, else -1
static int findShortestFirstAttempt(int               graph_nodes,
                                    std::vector<int>  graph_from,
                                    std::vector<int>  graph_to,
                                    std::vector<long> ids,
                                    int               val)
{
    //! If color val not present in ids at least twice, return -1
    if (std::count(ids.cbegin(), ids.cend(), static_cast<long>(val)) < 2)
    {
        return -1;
    }

    //! Store connected edges in undirected graph
    std::vector<std::vector<int>> connected_nodes(graph_nodes);
    if (graph_from.size() == graph_to.size())
    {
        for (std::size_t i = 0; i < graph_from.size(); ++i)
        {
            //! Add graph nodes with 0-based indexing
            connected_nodes[graph_from[i] - 1].emplace_back(graph_to[i] - 1);
            connected_nodes[graph_to[i] - 1].emplace_back(graph_from[i] - 1);
        }
    }

    //! Find starting node, i.e. first node with color val
    int start_node {};
    
    for (int i = 0; i < static_cast<int>(ids.size()); ++i)
    {
        if (ids[i] == static_cast<long>(val))
        {
            start_node = i;
            break;
        }
    }
    
    /*
     * Alternatively, can use std::find_if
     *
    auto start_node_it = std::find_if(ids.cbegin(),
                                      ids.cend(),
                                      static_cast<long>(val));
    if (start_node_it != ids.cend())
    {
        start_node = std::distance(ids.cbegin(), start_node_it) - 1;
    }
     */

    //! Queue of nodes to process, initialize with start_node
    std::queue<int> nodes_todo {};
    nodes_todo.push(start_node);

    //! Output vector of shortest distances, O(n = graph_nodes) space
    //! Initialized with -1 except at start_node index, which is 0
    std::vector<int> shortest_distances(graph_nodes, -1);
    shortest_distances[start_node] = 0;

    while (not nodes_todo.empty())
    {
        const auto curr_node = nodes_todo.front();
        nodes_todo.pop();

        //! If connected nodes of curr_node have not been processed yet
        //! (distance == -1) then add each to queue and update distance
        for (const auto connected_node : connected_nodes[curr_node])
        {
            if (shortest_distances[connected_node] != -1)
            {
                //! Connected node has already been processed since distance is
                //! not -1 so skip it. With BFS, the node will always be visited
                //! at the earliest time. This is O(1) space instead of O(n),
                //! which a solution using a set of visited nodes would require
                continue;
            }
            
            //! Update distance of connected node
            shortest_distances[connected_node] =
                shortest_distances[curr_node] + 1;

            //! If connected_node has color matching val, return
            if (ids[connected_node] == static_cast<long>(val))
            {
                return shortest_distances[connected_node];
            }

            //! Otherwise add connected node to queue
            nodes_todo.push(connected_node);

        } // for (const auto connected_node : ...
        
    } // while (not nodes_todo.empty())

    //! A node with matching color was not connected at this point
    return -1;

} // static int findShortestFirstAttempt( ...

static int weightDS(const std::vector<std::vector<int>>& connected_nodes,
                    const std::vector<int>&              target_nodes,
                    int                                  node,
                    int                                  limit = -1)
{
    std::unordered_set<int>         visited_nodes {};
    std::queue<std::pair<int, int>> node_dist {};
    node_dist.emplace(node, 0);

    while (not node_dist.empty())
    {
        int curr_node;
        int curr_dist;
        std::tie(curr_node, curr_dist) = node_dist.front();
        node_dist.pop();

        if (visited_nodes.count(curr_node) > 0)
        {
            continue;
        }
        
        if (std::find(target_nodes.cbegin(), target_nodes.cend(), curr_node)
            != target_nodes.cend()
            && curr_node != node)
        {
            return curr_dist;
        }
        
        std::ignore = visited_nodes.emplace(curr_node);

        if (curr_dist == limit)
        {
            return -1;
        }
        
        for (const auto next_node : connected_nodes[curr_node])
        {
            if (0 == visited_nodes.count(next_node))
            {
                node_dist.emplace(next_node, curr_dist + 1);
            }
        }

    } // while (not node_dist.empty())
    
    return -1;

} // static int weightDS( ...

//! @brief Solution from HR discussion section
//! @param[in] graph_nodes Number of nodes
//! @param[in] graph_from  Vector of start nodes for each edge
//! @param[in] graph_to    Vector of end nodes for each edge
//! @param[in] ids         Color id per node
//! @param[in] val         Color id to match
//! @return Length of shortest path between two nodes of same color, else -1
static int findShortestDiscussionSolution(int               graph_nodes,
                                          std::vector<int>  graph_from,
                                          std::vector<int>  graph_to,
                                          std::vector<long> ids,
                                          int               val)
{
    //! Store connected edges in undirected graph
    std::vector<std::vector<int>> connected_nodes(graph_nodes);
    if (graph_from.size() == graph_to.size())
    {
        for (std::size_t i = 0; i < graph_from.size(); ++i)
        {
            //! Add graph nodes with 0-based indexing
            connected_nodes[graph_from[i] - 1].emplace_back(graph_to[i] - 1);
            connected_nodes[graph_to[i] - 1].emplace_back(graph_from[i] - 1);
        }
    }

    std::vector<int> target_nodes {};

    for (int node_idx = 0; node_idx < static_cast<int>(ids.size()); ++node_idx)
    {
        if (ids[node_idx] == static_cast<long>(val))
        {
            target_nodes.emplace_back(node_idx);
        }
    }

    int shortest_distance {-1};
    for (const auto node : target_nodes)
    {
        const auto w = weightDS(connected_nodes,
                                target_nodes,
                                node,
                                shortest_distance);
        if (w > 0 && w < shortest_distance || shortest_distance == -1)
        {
            shortest_distance = w;
        }
    }

    return shortest_distance;

} // static int findShortestDiscussionSolution( ...

// Test case 0
TEST(FindShortestTest, TestCase0) {
    EXPECT_EQ(1, findShortestFirstAttempt(4,
                                          {1, 1, 4},
                                          {2, 3, 2},
                                          {1L, 2L, 1L, 1L},
                                          1));

    EXPECT_EQ(1, findShortestDiscussionSolution(4,
                                                {1, 1, 4},
                                                {2, 3, 2},
                                                {1L, 2L, 1L, 1L},
                                                1));
}

// Test case 1
TEST(FindShortestTest, TestCase1) {
    EXPECT_EQ(-1, findShortestFirstAttempt(4,
                                           {1, 1, 4},
                                           {2, 3, 2},
                                           {1L, 2L, 3L, 4L},
                                           2));

    EXPECT_EQ(-1, findShortestDiscussionSolution(4,
                                                 {1, 1, 4},
                                                 {2, 3, 2},
                                                 {1L, 2L, 3L, 4L},
                                                 2));
}

// Test case 2
TEST(FindShortestTest, TestCase2) {
    EXPECT_EQ(3, findShortestFirstAttempt(5,
                                          {1, 1, 2, 3},
                                          {2, 3, 4, 5},
                                          {1L, 2L, 3L, 3L, 2L},
                                          2));

    EXPECT_EQ(3, findShortestDiscussionSolution(5,
                                                {1, 1, 2, 3},
                                                {2, 3, 4, 5},
                                                {1L, 2L, 3L, 3L, 2L},
                                                2));
}