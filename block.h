#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>

using namespace std;

class Block {
    protected:
        vector<pair<int, int>> currBlockCoords; // coordinates of the block current
        vector<pair<int, int>> nextBlockCoords; // coordinates of the block after update (do boundary checks on this)
        char blockType;
        int currOrientation;
        int nextOrientation;
    public:
        Block();
        virtual ~Block();
        virtual void down() = 0;
        virtual void left() = 0;
        virtual void right() = 0;
        virtual void rotatec() = 0;
        virtual void rotatecc() = 0;
        virtual void render() = 0;
        virtual void undo() = 0; // if nextBlockCoords are invalid, clear next block coordinates
        virtual vector<pair<int, int>> getCurrCoords() = 0;
        virtual vector<pair<int, int>> getNextCoords() = 0;
        virtual char getBlockType() = 0;
};

#endif
