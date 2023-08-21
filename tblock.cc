#include "tblock.h"

TBlock::TBlock() {
    pair<int, int> coord1 = {3, 0}; // row, col
    pair<int, int> coord2 = {3, 1};
    pair<int, int> coord3 = {3, 2};
    pair<int, int> coord4 = {4, 1};
    currBlockCoords = {coord1, coord2, coord3, coord4};
    blockType = 'T';
    currOrientation = 1;
}

TBlock::~TBlock() {}

// Increase row
void TBlock::down() {
    for (auto coord : currBlockCoords) {
        int row = coord.first + 1;
        int col = coord.second;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Decrease Col
void TBlock::left() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second - 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Increase Col
void TBlock::right() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second + 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

void TBlock::rotatec() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first-1, currBlockCoords[0].second+1};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second-1};
        p4 = {currBlockCoords[3].first-1, currBlockCoords[3].second-1};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+2, currBlockCoords[0].second+1};
        p2 = {currBlockCoords[1].first+1, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first, currBlockCoords[2].second-1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second+1};
        nextOrientation = 3;
    }
    else if (currOrientation == 3) {
        p1 = {currBlockCoords[0].first, currBlockCoords[0].second-2};
        p2 = {currBlockCoords[1].first-1, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first-2, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second};
        nextOrientation = 4;
    }
    else if (currOrientation == 4) {
        p1 = {currBlockCoords[0].first-1, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second+2};
        p4 = {currBlockCoords[3].first+1, currBlockCoords[3].second};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void TBlock::rotatecc() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first+1, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second-2};
        p4 = {currBlockCoords[3].first-1, currBlockCoords[2].second-1};
        nextOrientation = 4;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+1, currBlockCoords[0].second-1};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second+1};
        p4 = {currBlockCoords[3].first+1, currBlockCoords[3].second+1};
        nextOrientation = 1;
    }
    else if (currOrientation == 3) {
        p1 = {currBlockCoords[0].first-2, currBlockCoords[0].second-1};
        p2 = {currBlockCoords[1].first-1, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first, currBlockCoords[2].second+1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second-1};
        nextOrientation = 2;
    }
    else if (currOrientation == 4) {
        p1 = {currBlockCoords[0].first, currBlockCoords[0].second+2};
        p2 = {currBlockCoords[1].first+1, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first+2, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second};
        nextOrientation = 3;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void TBlock::render() {
    currBlockCoords = nextBlockCoords;
    currOrientation = nextOrientation;
    nextBlockCoords.clear();
}

void TBlock::undo() {
    nextBlockCoords.clear();
}

vector<pair<int, int>> TBlock::getCurrCoords() { return currBlockCoords; }

vector<pair<int, int>> TBlock::getNextCoords() { return nextBlockCoords; }

char TBlock::getBlockType() { return blockType; }
