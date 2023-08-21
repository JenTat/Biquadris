#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class LBlock: public Block {
    public:
        LBlock();
        ~LBlock();
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
