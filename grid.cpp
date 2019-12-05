
#include "grid.h"
#include "grid_given.cpp"

// PA1 functions

/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid()
{ /*your code here*/
    clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count)
{ /* your code here */
    r %= numRows();
    if (r < 0 || r >= headOfRow_.size())
    {
        return;
    }
    count %= headOfCol_.size();

    Node *center = headOfRow_[r];
    Node *top = center->up;
    Node *dow = center->down;

    for (int i = 0; i < headOfCol_.size(); i++)
    {
        center = top->down;
        for (int j = 0; j < count; j++)
        {
            center = center->left;
        }
        top->down = center;
        center->up = top;
        dow->up = center;
        center->down = dow;
        top = top->right;
        dow = dow->right;

        if (r == 0)
        {
            headOfCol_[i] = center;
        }
    }

    headOfRow_[r] = center->right;
}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2). 
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count)
{ /* your code here */
    c %= numCols();
    if (headOfCol_.size() <= c || c < 0)
    {
        return;
    }
    count %= headOfRow_.size();
    Node *center = headOfCol_[c];
    Node *right = center->right;
    Node *left = center->left;

    for (int i = 0; i < headOfRow_.size(); i++)
    {
        center = right->left;
        for (int j = 0; j < count; j++)
        {
            center = center->up;
        }
        right->left = center;
        center->right = right;
        left->right = center;
        center->left = left;
        right = right->down;
        left = left->down;
        if (c == 0)
            headOfRow_[i] = center;
    }
    headOfCol_[c] = center->down;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear()
{ /*your code here*/
    for (int i = 0; i < headOfRow_.size(); i++)
    {
        Node *dummy = headOfRow_[i];
        if (dummy == NULL)
        {
            continue;
        }
        Node *next = dummy->right;
        while (next != dummy)
        {
            next = next->right;
            delete next->left;
        }
        delete next;
        headOfRow_[i] = NULL;
    }
    bwidth_ = 0;
    bheight_ = 0;
}

/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const &other)
{ /*your code here*/
    int row = other.numRows();
    int col = other.numCols();
    vector<vector<Node *>> nodes;
    for (int i = 0; i < row; i++)
    {
        vector<Node *> hold;
        Node *dummy = other.headOfRow_[i];
        for (int j = 0; j < col; j++)
        {
            Node *temp = new Node(dummy->block);
            hold.push_back(temp);
            dummy = dummy->right;
        }
        nodes.push_back(hold);
    }
    //C++ still is incredibly annoying.
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Node *node = nodes[i][j];
            node->up = nodes[(i == 0) ? row - 1 : i - 1][j];
            node->down = nodes[(i == row - 1) ? 0 : i + 1][j];
            node->left = nodes[i][(j == 0) ? col - 1 : j - 1];
            node->right = nodes[i][(j == col - 1) ? 0 : j + 1];
        }
    }
    for (int i = 0; i < other.numRows(); i++)
    {
        headOfRow_.push_back(nodes[i][0]);
    }
    for (int j = 0; j < other.numCols(); j++)
    {
        headOfCol_.push_back(nodes[0][j]);
    }
    bheight_ = other.bheight_;
    bwidth_ = other.bwidth_;
}