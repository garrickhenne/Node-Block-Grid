#include "block.h"

/**
 * Returns the width of the block.
 */
int Block::width() const{/*your code here*/
    return data[0].size();
}

/**
 * Returns the height of the block.
 */
int Block::height() const{/*your code here*/
    return data.size();
}

/**
 * Default Block constructor.
 */
Block::Block() {/* nothing */}

/**
 * Useful Block constructor.
 * Makes a block from the rectangle of width by height pixels in im
 * whose upper-left corner is at position (x,y).
 */
Block::Block(PNG & im, int x, int y, int width, int height) {/*your code here*/
    for (int row = 0; row < height; row++) {
        vector<HSLAPixel > rowVector;
        for (int col = 0; col < width; col++) {
            HSLAPixel *p = im.getPixel(x+col,y+row);
            rowVector.push_back(*p);
        }
        data.push_back(rowVector);
    }


}

/**
 * Draws the block at position (x,y) in the image im
 */
void Block::render(PNG & im, int x, int y) const {/*your code here*/
    unsigned int maxHeight = height();
    unsigned int maxWidth = width();

    for (unsigned int row = 0; row < maxHeight && row+y < im.height(); row++) {
        vector<HSLAPixel> rowVector = data[row];
        for (unsigned int col = 0; col < maxWidth && col+x < im.width(); col++) {
            HSLAPixel *p = im.getPixel(x+col,y+row);
            *p = rowVector[col];
        }
    }
    

}

/**
 * Changes the saturation of every pixel in the block to 0,
 * which removes the color, leaving grey.
 */
void Block::greyscale() {/*your code here*/
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            data[i][j].s = 0;
        }
    }
}
