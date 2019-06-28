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
    this->distance = 0;
    this->nodeReferences = new Node*[map.length()];
}

void BFS::run()
{
    generateMap();
    nodeQueue.push(startNode);
    Timer t("BFS");
    cout << "STATUS: " << (solve() ? "SOLVED" : "NO PATH") << endl;
    File f("output.txt");
    f.write(map);
}

void BFS::generateMap()
{
    for (int i = 0; i < map.length(); i++)
    {
        nodeReferences[i] = NULL;                           // Set the default value to NULL
        if (map[i] == '1' || map[i] == '\n') continue;      // skip if current index's content is 1 or newline
        if (!isJunction(i)) continue;                       // Do not add a node if the current position is not a node.

        Node* newNode = new Node();                         // Create new node
        newNode->distance = -1;                             // Set the node's distance data with a default value 

        if (map[i] == '2')
        {
            this->startNode = newNode;                      // Set newNode as the starting point if current index's content is 2
            newNode->distance = 0;
            newNode->sourceIndex = i;
        }
        nodeReferences[i] = newNode;                        // Store the reference to the new node in an array of node pointers

        newNode->data = map[i];                             // Set the node's data with the current index's content
        newNode->index = i;                                 // Set the node's index number with current index
        checkNodeSurroundings(newNode, i);                  // Checks the surrounding nodes and make a link between it
    }
}

void BFS::checkNodeSurroundings(Node* node, int index)
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

bool BFS::isJunction(int index)
{
    // A method that checks if a box located at a specific index can be assigned as a junction.
    // Used to generate graph

    bool up = false, right = false, down = false, left = false;
    
    // Check up
    if (index - spacing > 0)
        if (map[index - spacing] == '0' || map[index - spacing] == '2' || map[index - spacing] == '3') up = true;
    // Check down
    if (index + spacing < map.length())
        if (map[index + spacing] == '0' || map[index + spacing] == '2' || map[index + spacing] == '3') down = true;
    // Check left
    if (index - 1 > 0)
        if (map[index - 1] == '0' || map[index - 1] == '2' || map[index - 1] == '3') left = true;
    // Check right
    if (index + 1 < map.length())
        if (map[index + 1] == '0' || map[index + 1] == '2' || map[index + 1] == '3') right = true;
    
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
    // cout << "Distance: " << distance << ", Queue size: " << nodeQueue.size() << endl;
    queue<Node*> checkedNode;
    // Check if a node in the queue is '3'
    while (!nodeQueue.empty())                              // Loop through until all nodes in the main queue is empty
    {
        if (nodeQueue.front()->data == '3') 
        {
            Node* currentNode = nodeQueue.front();
            distance++;
            currentNode->distance = distance;

            // Backtrack to main
            while (true)
            {
                if (currentNode->data == '2') return true;
                distance = currentNode->distance;
                if (currentNode->up != NULL && currentNode->up->index == currentNode->sourceIndex)
                {
                    for (int i = currentNode->index; i >= currentNode->up->index; i = i - spacing) map[i] = '4';
                    // distance = currentNode->up->distance;
                    currentNode = currentNode->up;
                }
                else if (currentNode->left != NULL && currentNode->left->index == currentNode->sourceIndex)
                {
                    for (int i = currentNode->index; i >= currentNode->left->index; i--) map[i] = '4';
                    // distance = currentNode->left->distance;
                    currentNode = currentNode->left;
                }
                else if (currentNode->down != NULL && currentNode->down->index == currentNode->sourceIndex)
                {
                    for (int i = currentNode->index; i < currentNode->down->index; i = i + spacing) map[i] = '4';
                    // distance = currentNode->down->distance;
                    currentNode = currentNode->down;
                }
                else if (currentNode->right != NULL && currentNode->right->index == currentNode->sourceIndex)
                {
                    for (int i = currentNode->index; i < currentNode->right->index; i++) map[i] = '4';
                    // distance = currentNode->right->distance;
                    currentNode = currentNode->right;
                }
                else
                {
                    cout << "SHIT" << endl;
                    break;
                }
                

                // if (distance > -1) cout << "Backtracking on level " << distance << ", currentNodeIndex: " << currentNode->index << endl;
                // if (currentNode->data == '2') return true;
                // distance = currentNode->distance;
                // if (currentNode->up != NULL && currentNode->up->distance < distance)
                // {
                //     for (int i = currentNode->index; i >= currentNode->up->index; i = i - spacing) map[i] = '4';
                //     // distance = currentNode->up->distance;
                //     currentNode = currentNode->up;
                // }
                // else if (currentNode->left != NULL && currentNode->left->distance < distance)
                // {
                //     for (int i = currentNode->index; i >= currentNode->left->index; i--) map[i] = '4';
                //     // distance = currentNode->left->distance;
                //     currentNode = currentNode->left;
                // }
                // else if (currentNode->down != NULL && currentNode->down->distance < distance)
                // {
                //     for (int i = currentNode->index; i < currentNode->down->index; i = i + spacing) map[i] = '4';
                //     // distance = currentNode->down->distance;
                //     currentNode = currentNode->down;
                // }
                // else if (currentNode->right != NULL && currentNode->right->distance < distance)
                // {
                //     for (int i = currentNode->index; i < currentNode->right->index; i++) map[i] = '4';
                //     // distance = currentNode->right->distance;
                //     currentNode = currentNode->right;
                // }
                // else
                // {
                //     cout << "SHIT!" << endl;
                //     break;
                // }
                
            }

            return true;    // Return true if the end point is found
        }
        checkedNode.push(nodeQueue.front());                // Push the front node in the queue and put it into the checkedNode queue
        nodeQueue.front()->isVisited = true;                // Set isVisited value to true on the node
        nodeQueue.pop();                                    // Remove the node from the queue
    }

    distance++;
    // Queue next nodes
    while (!checkedNode.empty())                            // Loop through until all nodes in the checkedNodes is empty
    {
        // Add the nodes that needs to be checked later after 
        Node* currentNode = checkedNode.front();
        currentNode->distance = distance;
        if (currentNode->up != NULL && !currentNode->up->isVisited && !currentNode->up->willBeVisited)
        {
            currentNode->up->willBeVisited = true;
            currentNode->up->sourceIndex = currentNode->index;
            nodeQueue.push(currentNode->up);
        }
        if (currentNode->down != NULL && !currentNode->down->isVisited && !currentNode->down->willBeVisited)
        {
            currentNode->down->willBeVisited = true;
            currentNode->down->sourceIndex = currentNode->index;
            nodeQueue.push(currentNode->down);
        }
        if (currentNode->left != NULL && !currentNode->left->isVisited && !currentNode->left->willBeVisited)
        {
            currentNode->left->willBeVisited = true;
            currentNode->left->sourceIndex = currentNode->index;
            nodeQueue.push(currentNode->left);
        }
        if (currentNode->right != NULL && !currentNode->right->isVisited && !currentNode->right->willBeVisited)
        {
            currentNode->right->willBeVisited = true;
            currentNode->right->sourceIndex = currentNode->index;
            nodeQueue.push(currentNode->right);
        }
        checkedNode.pop();
    }

    // Run solve method recursively until it hits base case
    return solve();
}