#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

#include <vector>
#include <deque>
#include <memory>
#include <iostream>
#include <map>
#include <random>
#include <fstream>
#include <algorithm>

using namespace std;

class Board {
    int width;
    int length;

    protected:
        int score;
        deque<vector<char>> grid; // may need to change this to be a deque instead
        shared_ptr<Block> nextBlock;
        char nextBlockType;
        // shared_ptr<Block> currentBlock;
        vector<char> level0sequence;
        int level0sequencetracker = 0;
        bool nextBlockIsForced = false;

    public:
        Board();
        ~Board();
        vector<pair<shared_ptr<Block>, int>> allBlocks;
        void addToBlocks(shared_ptr<Block>, int);
        void chooseNextBlock(int level);
        shared_ptr<Block> getNextBlock();
        char getNextBlockType(); //temporary--> remove later (also remove from chooseNextBlock)
        void readscriptfile(string filename);
        int clearBlocks();
        int getBlockClearScore();
        void resetScore();
        void reset();
        void setNextBlock(char);
        deque<vector<char>> getGrid();
        void setElement(int row, int col, char c);
        void setNextBlockIsForced(bool);
        friend ostream& operator<<(ostream&, const Board&);
};

#endif
