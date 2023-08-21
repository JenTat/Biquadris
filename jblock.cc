#include "jblock.h"

JBlock::JBlock() {
    pair<int, int> coord1 = {3, 0}; // row, col
    pair<int, int> coord2 = {4, 0};
    pair<int, int> coord3 = {4, 1};
    pair<int, int> coord4 = {4, 2};
    currBlockCoords = {coord1, coord2, coord3, coord4};
    blockType = 'J';
    currOrientation = 1;
}

JBlock::~JBlock() {}

// Increase row
void JBlock::down() {
    for (auto coord : currBlockCoords) {
        int row = coord.first + 1;
        int col = coord.second;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Decrease Col
void JBlock::left() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second - 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Increase Col
void JBlock::right() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second + 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

void JBlock::rotatec() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;

    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first-1, currBlockCoords[0].second+1};
        p2 = {currBlockCoords[1].first-2, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second-1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second-2};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+2, currBlockCoords[0].second+1};
        p2 = {currBlockCoords[1].first+1, currBlockCoords[1].second+2};
        p3 = {currBlockCoords[2].first, currBlockCoords[2].second+1};
        p4 = {currBlockCoords[3].first-1, currBlockCoords[3].second};
        nextOrientation = 3;
    }
    else if (currOrientation == 3) {
        p1 = {currBlockCoords[0].first, currBlockCoords[0].second-2};
        p2 = {currBlockCoords[1].first+1, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first-1, currBlockCoords[3].second+1};
        nextOrientation = 4;
    }
    else if (currOrientation == 4) {
        p1 = {currBlockCoords[0].first-1, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first+2, currBlockCoords[3].second+1};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void JBlock::rotatecc() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first+1, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first-2, currBlockCoords[3].second-1};
        nextOrientation = 4;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+1, currBlockCoords[0].second-1};
        p2 = {currBlockCoords[1].first+2, currBlockCoords[1].second};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second+1};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second+2};
        nextOrientation = 1;
    }
    else if (currOrientation == 3) {
        p1 = {currBlockCoords[0].first-2, currBlockCoords[0].second-1};
        p2 = {currBlockCoords[1].first-1, currBlockCoords[1].second-2};
        p3 = {currBlockCoords[2].first, currBlockCoords[2].second-1};
        p4 = {currBlockCoords[3].first+1, currBlockCoords[3].second};
        nextOrientation = 2;
    }
    else if (currOrientation == 4) {
        p1 = {currBlockCoords[0].first, currBlockCoords[0].second+2};
        p2 = {currBlockCoords[1].first-1, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first+1, currBlockCoords[3].second-1};
        nextOrientation = 3;
    }
    nextBlockCoords = {p1, p2, p3, p4};
}

void JBlock::render() {
    currBlockCoords = nextBlockCoords;
    currOrientation = nextOrientation;
    nextBlockCoords.clear();
}

void JBlock::undo() {
    nextBlockCoords.clear();
}

vector<pair<int, int>> JBlock::getCurrCoords() { return currBlockCoords; }

vector<pair<int, int>> JBlock::getNextCoords() { return nextBlockCoords; }

char JBlock::getBlockType() { return blockType; }
