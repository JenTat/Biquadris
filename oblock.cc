#include "oblock.h"

OBlock::OBlock() {
    pair<int, int> coord1 = {3, 0}; // row, col
    pair<int, int> coord2 = {3, 1};
    pair<int, int> coord3 = {4, 0};
    pair<int, int> coord4 = {4, 1};
    currBlockCoords = {coord1, coord2, coord3, coord4};
    blockType = 'O';
}

OBlock::~OBlock() {}

// Increase row
void OBlock::down() {
    for (auto coord : currBlockCoords) {
        int row = coord.first + 1;
        int col = coord.second;
        nextBlockCoords.push_back({row, col});
    }
}

// Decrease Col
void OBlock::left() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second - 1;
        nextBlockCoords.push_back({row, col});
    }
}

// Increase Col
void OBlock::right() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second + 1;
        nextBlockCoords.push_back({row, col});
    }
}

void OBlock::rotatec() { nextBlockCoords = currBlockCoords; } 

void OBlock::rotatecc() { nextBlockCoords = currBlockCoords; }

void OBlock::render() {
    currBlockCoords = nextBlockCoords;
    nextBlockCoords.clear();
}

void OBlock::undo() {
    nextBlockCoords.clear();
}

vector<pair<int, int>> OBlock::getCurrCoords() { return currBlockCoords; }

vector<pair<int, int>> OBlock::getNextCoords() { return nextBlockCoords; }

char OBlock::getBlockType() { return blockType; }
