#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class OBlock: public Block {
    public:
        OBlock();
        ~OBlock();
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
