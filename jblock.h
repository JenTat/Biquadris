#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"
#include <vector>

using namespace std;

class JBlock: public Block {
    public:
        JBlock();
        ~JBlock();
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
