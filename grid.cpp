#include "grid.h"
#include "grid_given.cpp"

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ /*your code here*/
    clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) { /* your code here */
    r = r % numRows();
    int remainingRotations = count;

    //--Set surrounding nodes to new head node--

    int nodeSwitches = 0;
    int colIndex = 0;
    while (nodeSwitches < (int) headOfCol_.size()) {
        //Set first column nodes to new head node
        
        headOfRow_[r]->up->down = headOfRow_[r]->left;
        headOfRow_[r]->down->up = headOfRow_[r]->left;

        //Set old head node to new last column nodes
        headOfRow_[r]->up = headOfRow_[r]->up->right;
        headOfRow_[r]->down = headOfRow_[r]->down->right;

        if (r == 0) {
            headOfCol_[colIndex] = headOfCol_[colIndex]->left;
        }

        //Set headOfRow to next node, dont if the next node is desired new head node
        if (nodeSwitches < (int) headOfCol_.size()-1) {
            headOfRow_[r] = headOfRow_[r]->right;
        }
        

        nodeSwitches++;
        colIndex++;
    }

    remainingRotations--;
    if (remainingRotations != 0) {
        rotateR(r,remainingRotations);
    }
}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2). 
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count) { /* your code here */
    c = c % numCols();
    int remainingRotations = count;

    //--Set surrounding nodes to new head node--

    int nodeSwitches = 0;
    int rowIndex = 0;
    while (nodeSwitches < (int) headOfRow_.size()) {
        //Set first column nodes to new head node
        
        headOfCol_[c]->left->right = headOfCol_[c]->up;
        headOfCol_[c]->right->left = headOfCol_[c]->up;

        //Set old head node to new last row nodes
        headOfCol_[c]->left = headOfCol_[c]->left->down;
        headOfCol_[c]->right = headOfCol_[c]->right->down;

        if (c == 0) {
            headOfRow_[rowIndex] = headOfRow_[rowIndex]->up;
        }

        //Set headOfCol to next node, dont if the next node is desired new head node
        if (nodeSwitches < (int) headOfRow_.size()-1) {
            headOfCol_[c] = headOfCol_[c]->down;
        }
        

        nodeSwitches++;
        rowIndex++;
    }

    remainingRotations--;
    if (remainingRotations != 0) {
        rotateR(c,remainingRotations);
    }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear() { /*your code here*/
    for (int i = 0; i < (int) headOfRow_.size(); i++) {
        headOfRow_[i] = headOfRow_[i]->right;
        delete(headOfRow_[i]->left);
        if (headOfRow_[i]->right != NULL) {
            headOfRow_[i] = headOfRow_[i]->right;
            delete(headOfRow_[i]->left);
        } else {
            delete(headOfRow_[i]);
            headOfRow_[i] = NULL;
        }
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
void Grid::copy(Grid const& other) { /*your code here*/
    


    bheight_ = other.bheight_;
    bwidth_ = other.bwidth_;
    
    
    
    

}
