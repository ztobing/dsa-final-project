//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  bfs.cpp
//  A solving implementation using breadth first search method.
//  This method works by generating nodes on every junction on a map,
//  linking the nodes then do the BFS algorithm on every node.
//

#include "bfs.hpp"

BFS::BFS(string map, int start, int end, int spacing)
{
    this->map = map;
    this->start = start;
    this->end = end;
    this->spacing = spacing;
    this->nodeReferences = new Node*[map.length()];
}

void BFS::run()
{
    Timer t("BFS");
    generateMap();
    nodeQueue.push(startNode);
    cout << "STATUS: " << (solve() ? "SOLVED" : "NO PATH") << endl;
    cout << map << endl;
}

void BFS::generateMap()
{
    for (int i = 0; i < map.length(); i++)
    {
        nodeReferences[i] = NULL;
        if (map[i] == '1' || map[i] == '\n') continue;
        if (!isJunction(i)) continue;

        Node* newNode = new Node();
        if (map[i] == '2') this->startNode = newNode;
        nodeReferences[i] = newNode;

        newNode->data = map[i];
        checkNodeSurroundings(newNode, i);
    }
}

void BFS::checkNodeSurroundings(Node* node, int index)
{
    // Check top
    if (index - spacing > 0)
    {
        // Check if there's a node on top of a node
        for (int i = index - spacing; i > 0; i = i - spacing)
        {
            if (map[i] == '1') break;
            if (nodeReferences[i] != NULL)
            {
                node->up = nodeReferences[i];
                node->up->down = node;
                break;
            }
        }
    }

    // Check left
    if (index - 1 > 0)
    {
        for (int i = index - 1; i > 0; i--)
        {
            if (map[i] == '1') break;
            if (nodeReferences[i] != NULL)
            {
                node->left = nodeReferences[i];
                node->left->right = node;
                break;
            }
        }
    }
}

bool BFS::isJunction(int index)
{
    bool up = false, right = false, down = false, left = false;
    
    // Check up
    if (index - spacing > 0)
        if (map[index - spacing] == '0') up = true;
    // Check down
    if (index + spacing < map.length())
        if (map[index + spacing] == '0') down = true;
    // Check left
    if (index - 1 > 0)
        if (map[index - 1] == '0') left = true;
    // Check right
    if (index + 1 < map.length())
        if (map[index + 1] == '0') right = true;
    
    // Check if junction
    if ((up && left) || (up && right) || (down && left) || (down && right))
        return true;
    // Check if dead end
    if ((up ^ down) ^ (left ^ right))
        return true;
    
    return false;
}

bool BFS::solve()
{
    // Base case
    if (nodeQueue.empty()) return false;

    queue<Node*> checkedNode;
    // Check if a node in the queue is '3'
    while (!nodeQueue.empty())
    {
        if (nodeQueue.front()->data == '3') return true;
        checkedNode.push(nodeQueue.front());
        nodeQueue.front()->isVisited = true;
        nodeQueue.pop();
    }

    // Queue next nodes
    while (!checkedNode.empty())
    {
        Node* currentNode = checkedNode.front();
        if (currentNode->up != NULL && !currentNode->up->isVisited) nodeQueue.push(currentNode->up);
        if (currentNode->down != NULL && !currentNode->down->isVisited) nodeQueue.push(currentNode->down);
        if (currentNode->left != NULL && !currentNode->left->isVisited) nodeQueue.push(currentNode->left);
        if (currentNode->right != NULL && !currentNode->right->isVisited) nodeQueue.push(currentNode->right);
        checkedNode.pop();
    }
    return solve();
}