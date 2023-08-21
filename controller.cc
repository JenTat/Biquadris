#include "controller.h"

Controller::Controller(int level1, int level2): 
level1{level1}, level2{level2}, board1{make_unique<Board>()}, board2{make_unique<Board>()} {}

Controller::~Controller() {}

void Controller::setStartLevelBlock(){
    board1->chooseNextBlock(level1);
    board2->chooseNextBlock(level2);
}

void Controller::print() {
    cout << "\t\tHISCORE: " << hiscore << "\t" << endl;
    cout << "PLAYER 1\t\t\t" << "PLAYER 2" << endl;
    cout << "Level: " << level1 << "\t\t\t" << "Level: " << level2 << endl;
    cout << "Score: " << score1 << "\t\t\t" << "Score: " << score2 << endl;

    cout << "-----------" << "\t\t\t" << "-----------" << endl;

    for (size_t i = 0; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            if (player1EarnedSpecialAction && player1SpecialAction == 0) {
                if (i >= 6 && i <= 15 && j >= 2 && j <= 8) {
                    cout << '?';
                    continue;
                }
            }
            if (board1->getGrid()[i][j] == '.') {
                cout << '.';
                continue;
            }
            cout << board1->getGrid()[i][j];    
        }

        cout << "\t\t\t";
        
        for (size_t j = 0; j < 11; j++) {
            if (player2EarnedSpecialAction && player2SpecialAction == 0) {
                if (i >= 6 && i <= 15 && j >= 2 && j <= 8) {
                    cout << '?';
                    continue;
                }
            }
            if (board2->getGrid()[i][j] == '.') {
                cout << '.';
                continue;
            }    
            cout << board2->getGrid()[i][j];
        }
        
        cout << endl;
    }
    cout << "-----------" << "\t\t\t" << "-----------" << endl;

    // TODO: add getNextBlock to board class
    cout << "Next Block: " << "\t\t\t" << "Next Block: " << endl;
    cout << board1->getNextBlockType() << "\t\t\t\t" << board2->getNextBlockType() <<endl;
    if (isPlayer1Turn()){
        cout << "Player 1's turn. Please enter a command: ";
    }
    else{
        cout << "Player 2's turn. Please enter a command: ";
    }
}

void Controller::drawGame(Xwindow & w) {
    w.drawInfo(hiscore, level1, level2, score1, score2);
    w.drawBoard(board1->getGrid(), 20, 50, 20);
    w.drawBoard(board2->getGrid(), 260, 50, 20);
    w.drawNextBlock(board1->getNextBlockType(), 10, 20, 430);
    w.drawNextBlock(board2->getNextBlockType(), 10, 260, 430);
    //blind
    /*
    if (player1SpecialAction == 0){
        w.blind(1);
    }
    else if (player1SpecialAction == 0){
        w.blind(2);
    */
}

bool Controller::isInBoundary() {
    // Check if coords are within the boundary
    // Returns true if it is in boundary and false if it is not
    vector<pair<int, int>> currCoords = currBlock->getCurrCoords();
    vector<pair<int, int>> nextCoords = currBlock->getNextCoords();
    bool isInBounds = true;
    deque<vector<char>> checkGrid;
    if (player1Turn) {
        checkGrid = board1->getGrid();
    } else {
        checkGrid = board2->getGrid();
    }

    for (size_t i=0; i < nextCoords.size(); i++) {
        if (nextCoords[i].first < 0 || nextCoords[i].first > 17) {
            return false;
        }
        if (nextCoords[i].second < 0 || nextCoords[i].second > 10) {
            return false;
        }
        // check if it is not '.' AND if it does not overlap with a current coordinate
        if (checkGrid[nextCoords[i].first][nextCoords[i].second] != '.') {
            bool overlapWithCurr = false;
            for (auto coord : currCoords) {
                if (nextCoords[i] == coord) {
                    overlapWithCurr = true;
                }
            } 
            if (!overlapWithCurr) { return false; }
        }
    }
    return isInBounds;
}

void Controller::processCommand(string input) { 
    if (input == "down") { 
        down();
    } else if (input == "right") {
        right();
        if ((player1Turn && player1EarnedSpecialAction && player1SpecialAction == 1) 
            || (!player1Turn && player2EarnedSpecialAction && player2SpecialAction == 1)) {
            currBlock->down();
            if (!isInBoundary()) {
                currBlock->undo();
                drop();
            } else {
                currBlock->down();
                if (!isInBoundary()) {
                    currBlock->undo();
                    drop();
                } else {
                    down();
                    down();
                }
            }
        }
    } else if (input == "left") {
        left();
        if ((player1Turn && player1EarnedSpecialAction && player1SpecialAction == 1) 
            || (!player1Turn && player2EarnedSpecialAction && player2SpecialAction == 1)) {
            currBlock->down();
            if (!isInBoundary()) {
                currBlock->undo();
                drop();
            } else {
                currBlock->down();
                if (!isInBoundary()) {
                    currBlock->undo();
                    drop();
                } else {
                    down();
                    down();
                }
            }
        }
    } else if (input == "drop") {
        drop();
    } else if (input == "clockwise") {
        rotatec();
    } else if (input == "counterclockwise") {
        rotatecc();
    }
    else if (input == "levelup"){
        if (player1Turn){
            setLevel1(level1 + 1);
        }
        else{
           setLevel2(level2 + 1); 
        }
    }
    else if (input == "leveldown"){
        if (player1Turn){
            setLevel1(level1 -1);
        }
        else{
           setLevel2(level2 -1); 
        }
    }
    else if (input == "sequence"){
        string filename;
        cin >> filename;
        ifstream seq;
        seq.open (filename);
        string command;
        while (seq >> command){
            processCommand(command);
        }
        seq.close();
    }
    else if (input == "reset"){
        reset();
    }

    print();
}

void Controller::chooseBlock() {
    if (player1Turn){
        currBlock = board1->getNextBlock();
        board1->addToBlocks(currBlock, level1);
        vector<pair<int, int>> coords = currBlock->getCurrCoords();
        for (auto coord : coords) {
            board1->setElement(coord.first, coord.second, currBlock->getBlockType());
        }
        board1->chooseNextBlock(level1);
    }
    else{
        currBlock = board2->getNextBlock();
        board2->addToBlocks(currBlock, level2);
        vector<pair<int, int>> coords = currBlock->getCurrCoords();
        for (auto coord : coords) {
            board2->setElement(coord.first, coord.second, currBlock->getBlockType());
        }
        board2->chooseNextBlock(level2);
    }
}

void Controller::drop() {
    currBlock->down();
    while (isInBoundary()) {
        setPosition();
        currBlock->down();
    }
    currBlock->undo();

    // Revert Special Action if there was any
    if (player1Turn && player1EarnedSpecialAction) {
        player1EarnedSpecialAction = false;
        player1SpecialAction = -1;
        board1->setNextBlockIsForced(false);
    } 
    
    if (!player1Turn && player2EarnedSpecialAction) {
        player2EarnedSpecialAction = false;
        player2SpecialAction = -1;
        board2->setNextBlockIsForced(false);
    }

    //once you drop, check if any rows can be cleared:
    clearBlocks();
    
    //after, you need set the current block for the next player and switch turns
    changeTurn();
    chooseBlock();
}

void Controller::down() {
    currBlock->down();
    if (!isInBoundary()) { 
        currBlock->undo();
        print();
        return; 
    }
    setPosition();
}

void Controller::left() {
    currBlock->left();
    if (!isInBoundary()) {
        currBlock->undo();
        return;
    }
    setPosition(); 
}

void Controller::right() {
    currBlock->right();
    if (!isInBoundary()) {
        currBlock->undo();
        return;
    }
    setPosition(); 
}

void Controller::rotatec() {
    currBlock->rotatec();
    if (!isInBoundary()) {
        currBlock->undo();
        return;
    }
    setPosition();
}

void Controller::rotatecc() {
    currBlock->rotatecc();
    if (!isInBoundary()) {
        currBlock->undo();
        return;
    }
    setPosition();
}

void Controller::setPosition() {
    vector<pair<int, int>> coords = currBlock->getCurrCoords(); // clear current coords before setting next
    for (auto coord : coords) {
        if (player1Turn) {
            board1->setElement(coord.first, coord.second, '.');
        } else {
            board2->setElement(coord.first, coord.second, '.');
        }
    }
    currBlock->render();

    coords = currBlock->getCurrCoords();
    for (auto coord : coords) {
        if (player1Turn) {
            board1->setElement(coord.first, coord.second, currBlock->getBlockType());
        } else {
            board2->setElement(coord.first, coord.second, currBlock->getBlockType());
        }     
    }
}

void Controller::clearBlocks() {
    int numRows;
    if (player1Turn) {
        numRows= board1->clearBlocks(); 
        if (numRows != 0){
            calculateScore(numRows);
            score1 += board1->getBlockClearScore();
            board1->resetScore();

        }
    }
    else {
        numRows = board2->clearBlocks();
        if (numRows != 0){
            calculateScore(numRows);
            score2 += board2->getBlockClearScore();
            board2->resetScore();

        }
    }

    if (numRows >= 2) {
        triggerSpecialAction();
    }
}

void Controller::setLevel1(int level1) { 
    if (level1 <= 4 && level1 >= 0){
        this->level1 = level1; 
    }
}
void Controller::setLevel2(int level2) { 
    if (level2 <= 4 && level2 >= 0){
        this->level2 = level2; 
    }
}

bool Controller::isPlayer1Turn() { return player1Turn; }

void Controller::changeTurn(){ player1Turn = !player1Turn; };

void Controller::readscriptfile1(string filename){
    board1->readscriptfile(filename);
}

void Controller::readscriptfile2(string filename){
    board2->readscriptfile(filename);
}

void Controller::calculateScore(int numRows) {
    if (player1Turn) {
        score1 += pow((level1+numRows),2);
        if (score1 > hiscore) {
            hiscore = score1;
        }
    }
    else {
        score2 += pow((level2+numRows),2);
        if (score2 > hiscore) {
            hiscore = score2;
        }
    }
}

int Controller::getStartLevel() { return startLevel;}
void Controller::setStartLevel(int l) { startLevel = l;}

void Controller::setup(){
    //setup: choose next and current blocks
    setStartLevelBlock();
    //set current block for player 1 and start the game
    chooseBlock();
}

void Controller::reset(){
    player1Turn = true;
    //reset each board
    board1->reset();
    board2->reset();
    //reset scores
    score1 = 0;
    score2 = 0;
    //levels set back to start levels
    level1 = getStartLevel();
    level2 = getStartLevel();
    //rechoose starting blocks
    setup();
}

void Controller::triggerSpecialAction() {
    // call special action
    // Ask player to choose special action
    print();

    string action;
    char block;
    cout << endl <<"Please choose your special action (blind, heavy, force): ";
    cin >> action;

    int specialAction;
    if (action == "blind") {
        specialAction = 0;
    } else if (action == "heavy") {
        specialAction = 1;
    } else if (action == "force") {
        specialAction = 2;
        cin >> block;
        if (player1Turn) {
            board2->setNextBlock(block);
            board2->setNextBlockIsForced(true);
        } else {
            board1->setNextBlock(block);
            board1->setNextBlockIsForced(true);
        }
    }

    if (player1Turn) {
        player2EarnedSpecialAction = true;
        player2SpecialAction = specialAction;
    } else {
        player1EarnedSpecialAction = true;
        player1SpecialAction = specialAction;
    }
}
