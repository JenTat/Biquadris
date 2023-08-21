#include "sblock.h"

SBlock::SBlock() {
    pair<int, int> coord1 = {3, 1}; // row, col
    pair<int, int> coord2 = {3, 2};
    pair<int, int> coord3 = {4, 0};
    pair<int, int> coord4 = {4, 1};
    currBlockCoords = {coord1, coord2, coord3, coord4};
    blockType = 'S';
    currOrientation = 1;
}

SBlock::~SBlock() {}

// Increase row
void SBlock::down() {
    for (auto coord : currBlockCoords) {
        int row = coord.first + 1;
        int col = coord.second;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Decrease Col
void SBlock::left() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second - 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

// Increase Col
void SBlock::right() {
    for (auto coord : currBlockCoords) {
        int row = coord.first;
        int col = coord.second + 1;
        nextBlockCoords.push_back({row, col});
    }
    nextOrientation = currOrientation;
}

void SBlock::rotatec() {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
    pair<int, int> p4;
    if (currOrientation == 1) {
        p1 = {currBlockCoords[0].first, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first+1, currBlockCoords[1].second-1};
        p3 = {currBlockCoords[2].first-2, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first-1, currBlockCoords[3].second-1};
        nextOrientation = 2;
    }
    else if (currOrientation == 2) {
        p1 = {currBlockCoords[0].first, currBlockCoords[0].second};
        p2 = {currBlockCoords[1].first-1, currBlockCoords[1].second+1};
        p3 = {currBlockCoords[2].first+2, currBlockCoords[2].second};
        p4 = {currBlockCoords[3].first+1, currBlockCoords[3].second+1};
        nextOrientation = 1;
    }
    nextBlockCoords = {p1, p2, p3, p4};
}

void SBlock::rotatecc() {
    rotatec();
}

void SBlock::render() {
    currBlockCoords = nextBlockCoords;
    currOrientation = nextOrientation;
    nextBlockCoords.clear();
}

void SBlock::undo() {
    nextBlockCoords.clear();
}

vector<pair<int, int>> SBlock::getCurrCoords() { return currBlockCoords; }

vector<pair<int, int>> SBlock::getNextCoords() { return nextBlockCoords; }

char SBlock::getBlockType() { return blockType; }
