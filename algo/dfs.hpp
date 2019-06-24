//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  dfs.hpp
//  A solving implementation using depth first search method.
//  This method works by generating nodes on every junction on a map,
//  linking the nodes then do the DFS algorithm on every node.
//

#ifndef dfs_hpp
#define dfs_hpp

#include <iostream>
#include "../util/timer.hpp"
#include "../util/file.hpp"

using namespace std;

class DFS
{
private:
    struct Node
    {
        char data;
        int index;
        bool isVisited = false;
        Node* up = NULL;
        Node* right = NULL;
        Node* down = NULL;
        Node* left = NULL;
    };
    string map;
    int start, end, spacing;
    Node* startNode;
    Node** nodeReferences;
    void generateMap();
    void checkNodeSurroundings(Node* node, int index);
    bool isJunction(int index);
    bool solve(Node* currentNode, Node* lastNode, int spacing);
public:
    DFS(string map, int start, int end, int spacing);
    ~DFS();
    void run();
};

#endif