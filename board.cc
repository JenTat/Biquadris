#include "board.h"

Board::Board() {
     // make 18 x 11 board (15 x 11 for play, 3 row for buffer)
     for (int r = 0; r < 18; r++) {
        vector<char> row;
        for (int c = 0; c < 11; c++) {
            row.push_back('.');
        }
        grid.push_back(row);
     }
}

Board::~Board() {}

deque<vector<char>> Board::getGrid() { return grid; }

void Board::addToBlocks(shared_ptr<Block> block, int level) {
    allBlocks.push_back({block, level});
}

int Board::clearBlocks() {
    int numRows = 0;
    int clearedCells;
    vector<int> rowsToClear;
    vector<char> row = {'.', '.', '.', '.', '.', '.', '.', '.','.','.', '.'};

    for (size_t i=0; i < grid.size(); i++) {
        clearedCells = 0;
        for (size_t j=0; j<grid[i].size(); j++) {
            if (grid[i][j] != '.') {
                clearedCells += 1;
            }
        }
        if (clearedCells == 11) {
            //mark rows we need to erase
            grid[i].push_back('!');
            rowsToClear.push_back(i);
            numRows += 1;
        }
    }


    // Block Scoring
    for (size_t n=0; n < allBlocks.size(); n++) {
        for (size_t m=0; m<rowsToClear.size(); m++) {
            if ((allBlocks[n].first->getCurrCoords()[0].first == rowsToClear[m]) &&
            (allBlocks[n].first->getCurrCoords()[1].first == rowsToClear[m]) &&
            (allBlocks[n].first->getCurrCoords()[2].first == rowsToClear[m]) &&
            (allBlocks[n].first->getCurrCoords()[3].first == rowsToClear[m])) {
                score += pow((allBlocks[n].second+1),2);
            }
        }
    }

    // Update Coordinates
    for (size_t n=0; n < allBlocks.size(); n++) {
        for (size_t m=0; m<rowsToClear.size(); m++) {
            if (allBlocks[n].first->getCurrCoords()[0].second > rowsToClear[m]) {
                allBlocks[n].first->getCurrCoords()[0].second -= 1;
            }
            if (allBlocks[n].first->getCurrCoords()[1].second > rowsToClear[m]) {
                allBlocks[n].first->getCurrCoords()[1].second -= 1;
            }
            if (allBlocks[n].first->getCurrCoords()[2].second > rowsToClear[m]) {
                allBlocks[n].first->getCurrCoords()[2].second -= 1;
            }
            if (allBlocks[n].first->getCurrCoords()[3].second > rowsToClear[m]) {
                allBlocks[n].first->getCurrCoords()[3].second -= 1;
            }
        }
    }

    //erase marked rows
    for (int i=0; i < numRows; i++){
        for (size_t k=0; k < grid.size(); k++) {
            if (find(grid[k].begin(), grid[k].end(), '!') != grid[k].end()){
                grid.erase(grid.begin() + k);
                break;
            }
        }
    }

    for (int r=0; r<numRows; r++) {
        grid.push_front(row);
    }

    return numRows;
}

int Board::getBlockClearScore() { return score; }

void Board::resetScore() { score = 0; }

// here for debugging purposes
ostream& operator<<(ostream& out, const Board& board) {
    for (size_t i = 0; i < board.grid.size(); i++) {
        for (size_t j = 0; j < board.grid[i].size(); j++) {
            if (board.grid[i][j] == '.') {
                out << '.';
            }    
        }
        out << endl;
    }
    out << "-----------" << endl;
    return out;
}

void Board::setElement(int row, int col, char c) { grid[row][col] = c; }

void Board::chooseNextBlock(int level) {
    int blockNum;
    char blockType;
    
    /* each block is numbered in this order with I as 0, T as 6
        I, J, L, O, S, Z, T
    */
    map<char, int> m;
    m['I'] = 0;
    m['J'] = 1;
    m['L'] = 2;
    m['O'] = 3;
    m['S'] = 4;
    m['Z'] = 5;
    m['T'] = 6;

    //level 0 set block based of sequence
    if (level == 0){ 
        blockType = level0sequence[level0sequencetracker];
        if (level0sequencetracker < int(level0sequence.size()) -1){
            level0sequencetracker += 1;
        }
        else{
            level0sequencetracker = 0;
        }
        blockNum = m[blockType];  
    }
    //use discrete distributions to choose the block for levels 1-4
    else{
        random_device rd;
        mt19937 gen(rd());

        //level 1: s and z are 1/12, others are 1/6
        if (level == 1){
            discrete_distribution<> distribution{2,2,2,2,1,1,2};
            blockNum = distribution(gen);
        }
        //level 2: equal
        else if (level == 2){
            discrete_distribution<> distribution{1,1,1,1,1,1,1};
            blockNum = distribution(gen);
        }
        //level 3 and 4: s and z are 2/9, others are 1/9
        else{
            discrete_distribution<> distribution{1,1,1,1,2,2,1};
            blockNum = distribution(gen);
        }
    }

    if (nextBlockIsForced) { return; }
  
    if (blockNum == 0){
        nextBlock = make_shared<IBlock>();
        nextBlockType = 'I';
    }
    else if (blockNum == 1){
        nextBlock = make_shared<JBlock>();
        nextBlockType = 'J';
    }
    else if (blockNum == 2){
        nextBlock = make_shared<LBlock>();
        nextBlockType = 'L';
    }
    else if (blockNum == 3){
        nextBlock = make_shared<OBlock>();
        nextBlockType = 'O';
    }
    else if (blockNum == 4){
        nextBlock = make_shared<SBlock>();
        nextBlockType = 'S';
    }
    else if (blockNum == 5){
        nextBlock = make_shared<ZBlock>();
        nextBlockType = 'Z';
    }
    else if (blockNum == 6){
        nextBlock = make_shared<TBlock>();
        nextBlockType = 'T';
    }
}

shared_ptr<Block> Board::getNextBlock(){
    return nextBlock;
}

void Board::setNextBlock(char blockType) {
    nextBlockType = blockType;
    switch (blockType)
    {
    case 'I':
        nextBlock = make_shared<IBlock>();
        break;
    case 'J':
        nextBlock = make_shared<JBlock>();
        break;
    case 'L':
        nextBlock = make_shared<LBlock>();
        break;
    case 'O':
        nextBlock = make_shared<OBlock>();
        break;
    case 'S':
        nextBlock = make_shared<SBlock>();
        break;
    case 'Z':
        nextBlock = make_shared<ZBlock>();
        break;
    case 'T':
        nextBlock = make_shared<TBlock>();
        break;
    default:
        break;
    }
}

void Board::setNextBlockIsForced(bool isForced) { nextBlockIsForced = isForced; }

char Board::getNextBlockType(){
    return nextBlockType;
};

void Board::readscriptfile(string filename){
    ifstream seq;
    seq.open (filename);
    level0sequence.clear();
    level0sequencetracker = 0;
    char b;
    while (seq >> b){
        level0sequence.push_back(b);
    }
    seq.close();

    /* for debug
    for (char c: level0sequence){
        cout << c;
    }
    cout << endl;
    */
}

void Board::reset(){
    //reset board
    for (size_t i=0; i < grid.size(); i++) {
        for (size_t j=0; j<grid[i].size(); j++) {
            grid[i][j] = '.';
        }
    }
    //if at level 0, go back to the start of the file
    level0sequencetracker = 0;
}
