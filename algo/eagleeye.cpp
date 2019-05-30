#include "eagleeye.hpp"

EagleEye::EagleEye(string map, int start, int end, int spacing)
{
    this->map = map;
    this->start = start;
    this->end = end;
    this->spacing = spacing;
    this->nodeReferences = new Node*[map.length()];
}

void EagleEye::run()
{
    generateMap();
    cout << map << endl;
}

void EagleEye::generateMap()
{
    for (int i = 0; i < map.length(); i++)
    {
        if (map[i] == '1' || map[i] == '\n' || map[i] == ' ') continue;
        if (!isJunction(i)) continue;


        Node* newNode = new Node();
        if (map[i] == '2') this->startNode = newNode;
        nodeReferences[i] = newNode;

        newNode->data = map[i];
        map[i] = ' '; // temp
        checkNodeSurroundings(newNode, i);
    }
}

void EagleEye::checkNodeSurroundings(Node* node, int index)
{
    // Check top
    if (index - spacing > 0)
    {
        // Check if there's a node on top of a node
        for (int i = index; i > 0; i - spacing)
        {
            if (map[i] == '1') break;
            if (nodeReferences[i] != NULL)
            {
                node->up = nodeReferences[i];
                node->up->down = node;
                break;
            }
            else
            {
                cout << "null" << endl;
            }
        }
    }

    // Check left
    if (index - 1 > 0)
    {
        for (int i = index; i > 0; i--)
        {
            if (map[i] == '1') break;
            if (nodeReferences[i] != NULL)
            {
                node->left = nodeReferences[i];
                node->left->right = node;
                break;
            }
            else
            {
                cout << "null" << endl;
            }
        }
    }
}

bool EagleEye::isJunction(int index)
{
    bool up, right, down, left = false;
    
    // Check up
    if (index - spacing > 0)
        if (map[index - spacing] == '0' || map[index - spacing] == ' ') up = true;
    // Check down
    if (index + spacing < map.length())
        if (map[index + spacing] == '0' || map[index + spacing] == ' ') down = true;
    // Check left
    if (index - 1 > 0)
        if (map[index - 1] == '0' || map[index - 1] == ' ') left = true;
    // Check right
    if (index + 1 > 0)
        if (map[index + 1] == '0' || map[index + 1] == ' ') right = true;
    
    // Check if junction
    if ((up && left) || (up && right) || (down && left) || (down && right))
        return true;
    // Check if dead end
    if (up ^ down ^ left ^ right)
        return true;
    
    return false;
}
