#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class ZBlock: public Block {
    public:
        ZBlock();
        ~ZBlock();
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
