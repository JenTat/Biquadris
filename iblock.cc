#include "iblock.h"

IBlock::IBlock() {
    pair<int, int> coord1 = {3, 0}; // row, col
    pair<int, int> coord2 = {3, 1};
    pair<int, int> coord3 = {3, 2};
    pair<int, int> coord4 = {3, 3};
    currBlockCoords = {coord1, coord2, coord3, coord4};
    blockType = 'I';
    currOrientation = 1;
}

IBlock::~IBlock() {}

// Increase row
void IBlock::down() {
    for (auto coord : currBlockCoords) {
        int row = coord.first + 1;
        int col = coord.second;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Decrease Col
void IBlock::left() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second - 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Increase Col
void IBlock::right() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second + 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

void IBlock::rotatec() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first-3, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first-2, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second-2};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second-3};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+3, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first+2, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second+2};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second+3};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void IBlock::rotatecc() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first-3, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first-2, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first-1, currBlockCoords[2].second-2};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second-3};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first+3, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first+2, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first+1, currBlockCoords[2].second+2};
        p4 = {currBlockCoords[3].first, currBlockCoords[3].second+3};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
} 

void IBlock::render() {
    currBlockCoords = nextBlockCoords;
    currOrientation = nextOrientation;
    nextBlockCoords.clear();
}

void IBlock::undo() {
    nextBlockCoords.clear();
}

vector<pair<int, int>> IBlock::getCurrCoords() { return currBlockCoords; }

vector<pair<int, int>> IBlock::getNextCoords() { return nextBlockCoords; }

char IBlock::getBlockType() { return blockType; }
