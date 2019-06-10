//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  bfs.hpp
//  A solving implementation using breadth first search method.
//  This method works by generating nodes on every junction on a map,
//  linking the nodes then do the BFS algorithm on every node.
//

#ifndef bfs_hpp
#define bfs_hpp

#include <iostream>
#include <queue>
#include "../util/timer.hpp"

using namespace std;

class BFS
{
private:
    struct Node
    {
        char data;
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
    queue<Node*> nodeQueue;
    void generateMap();
    void checkNodeSurroundings(Node* node, int index);
    bool isJunction(int index);
    bool solve();
public:
    BFS(string map, int start, int end, int spacing);
    void run();
};

#endif