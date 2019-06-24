//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  dfs.cpp
//  A solving implementation using depth first search method.
//  This method works by generating nodes on every junction on a map,
//  linking the nodes then do the DFS algorithm on every node.
//

#include "dfs.hpp"

DFS::DFS(string map, int start, int end, int spacing)
{
    this->map = map;
    this->start = start;
    this->end = end;
    this->spacing = spacing;
    this->nodeReferences = new Node*[map.length()];
}

DFS::~DFS()
{
    delete[] this->nodeReferences;
}

void DFS::run()
{
    Timer t("DFS");
    generateMap();
    cout << "STATUS: " << (solve(startNode->down, startNode, spacing) ? "SOLVED" : "NO PATH") << endl;
    cout << map << endl;
}

void DFS::generateMap()
{
    // Generate nodes for every junction and every dead end
    for (int i = 0; i < map.length(); i++)
    {
        nodeReferences[i] = NULL;                           // Set the default value to NULL
        if (map[i] == '1' || map[i] == '\n') continue;      // skip if current index's content is 1 or newline
        if (!isJunction(i)) continue;                       // Do not add a node if the current position is not a node.

        Node* newNode = new Node();                         // Create new node
        if (map[i] == '2') this->startNode = newNode;       // Set newNode as the starting point if current index's content is 2
        nodeReferences[i] = newNode;                        // Store the reference to the new node in an array of node pointers

        newNode->data = map[i];                             // Set the node's data with the current index's content
        newNode->index = i;                                 // Set the node's index number with current index
        checkNodeSurroundings(newNode, i);                  // Checks the surrounding nodes and make a link between it
    }
}

void DFS::checkNodeSurroundings(Node* node, int index)
{
    // Links a node to adjacent nodes by checking the presence of nodes in the north and west.

    // Check top
    if (index - spacing > 0)
    {
        // Check if there's a node on top of a node
        for (int i = index - spacing; i > 0; i = i - spacing)
        {
            if (map[i] == '1') break;           // Break if there is a wall
            if (nodeReferences[i] != NULL)      // If a node is found
            {
                node->up = nodeReferences[i];   // Link current node's north link to the adjacent node in the north
                node->up->down = node;          // Link currrent node's north down link to current node
                break;
            }
        }
    }

    // Check left
    if (index - 1 > 0)
    {
        for (int i = index - 1; i > 0; i--)
        {
            if (map[i] == '1') break;               // Break id there is a wall
            if (nodeReferences[i] != NULL)          // If a node is found
            {
                node->left = nodeReferences[i];     // Link current node's west link to the adjacent node in the west
                node->left->right = node;           // Link current node's west east link to current node
                break;
            }
        }
    }
}

bool DFS::isJunction(int index)
{
    // A method that checks if a box located at a specific index can be assigned as a junction.
    // Used to generate graph

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


bool DFS::solve(Node* currentNode, Node* lastNode, int spacing)
{
    // Solve the map by checking all possible path with left-right-down-up precedence
    currentNode->isVisited = true;

    // Base case
    if (currentNode->data == '3') return true;

    // Move left
    if (currentNode->left != NULL)
        if (currentNode->left != lastNode && !currentNode->left->isVisited)
            if (solve(currentNode->left , currentNode, spacing))
            {
                for (int i = currentNode->index; i >= currentNode->left->index; i--) map[i] = '4';
                return true;
            }
    
    // Move right
    if (currentNode->right != NULL)
        if (currentNode->right != lastNode && !currentNode->right->isVisited)
            if (solve(currentNode->right , currentNode, spacing))
            {
                for (int i = currentNode->index; i <= currentNode->right->index; i++) map[i] = '4';
                return true;
            }

    // Move down
    if (currentNode->down != NULL)
        if (currentNode->down != lastNode && !currentNode->down->isVisited)
            if (solve(currentNode->down , currentNode, spacing))
            {
                for (int i = currentNode->index; i <= currentNode->down->index; i = i + spacing) map[i] = '4';
                return true;
            }

    // Move up
    if (currentNode->up != NULL)
        if (currentNode->up != lastNode && !currentNode->up->isVisited)
            if (solve(currentNode->up , currentNode, spacing))
            {
                for (int i = currentNode->index; i >= currentNode->up->index; i = i - spacing) map[i] = '4';
                return true;
            }

    return false;
}