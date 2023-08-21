#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class IBlock: public Block {
    public:
        IBlock();
        ~IBlock();
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
