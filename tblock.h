#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class TBlock: public Block {
    public:
        TBlock();
        ~TBlock();
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
