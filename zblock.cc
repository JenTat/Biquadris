#include "zblock.h"

ZBlock::ZBlock() {
    pair<int, int> coord1 = {3, 0}; // row, col
    pair<int, int> coord2 = {3, 1};
    pair<int, int> coord3 = {4, 1};
    pair<int, int> coord4 = {4, 2};
    currBlockCoords = {coord1, coord2, coord3, coord4};
    blockType = 'Z';
    currOrientation = 1;
}

ZBlock::~ZBlock() {}

// Increase row
void ZBlock::down() {
    for (auto coord : currBlockCoords) {
        int row = coord.first + 1;
        int col = coord.second;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Decrease Col
void ZBlock::left() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second - 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Increase Col
void ZBlock::right() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second + 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

void ZBlock::rotatec() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first-1, currBlockCoords[0].second+1};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second-1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second-2};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+1, currBlockCoords[0].second-1};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second+1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second+2};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void ZBlock::rotatecc() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first-1, currBlockCoords[0].second+1};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second-1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second-2};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+1, currBlockCoords[0].second-1};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second+1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second+2};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void ZBlock::render() {
    currBlockCoords = nextBlockCoords;
    currOrientation = nextOrientation;
    nextBlockCoords.clear();
}

void ZBlock::undo() {
    nextBlockCoords.clear();
}

vector<pair<int, int>> ZBlock::getCurrCoords() { return currBlockCoords; }

vector<pair<int, int>> ZBlock::getNextCoords() { return nextBlockCoords; }

char ZBlock::getBlockType() { return blockType; }
