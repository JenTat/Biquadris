#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class SBlock: public Block {
    public:
        SBlock();
        ~SBlock();
        void down();
        void left();
        void right();
        void rotatec();
        void rotatecc();
        void render();
        void undo();
        vector<pair<int, int>> getCurrCoords();
        vector<pair<int, int>> getNextCoords();
        char getBlockType();
};

#endif
