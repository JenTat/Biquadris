#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "block.h"
#include "window.h"

#include <memory>
#include <vector>
#include <random>
#include <map>
#include <cmath>
#include <fstream>
#include <iostream>

class Controller {
    int hiscore = 0;
    int level1 = 0;
    int level2 = 0; // level for both players
    int score1 = 0;
    int score2 = 0; // score for both players
    int startLevel = 0;
    string userInput;
    int turns;
    int turnNum;
    bool player1Turn = true;
    bool player1EarnedSpecialAction = false;
    bool player2EarnedSpecialAction = false;
    int player1SpecialAction = -1; // -1: none, 0: Blind, 1: Heavy, 2: Force
    int player2SpecialAction = -1; // -1: none, 0: Blind, 1: Heavy, 2: Force
    shared_ptr<Block> currBlock;
    unique_ptr<Board> board1;
    unique_ptr<Board> board2;
    public:
        Controller(int, int);
        ~Controller();  
        void processCommand(string);
        void print();
        void drawGame();
        void chooseBlock();
        void drawGame(Xwindow & w);
        bool isInBoundary();
        void down();
        void left();
        void right();
        void rotatec();
        void rotatecc();
        void drop(); // while in bounds move down
        void setPosition();
        void setLevel1(int level1);
        void setLevel2(int level2);
        void readscriptfile1(string filename);
        void readscriptfile2(string filename);
        void setStartLevelBlock();
        bool isPlayer1Turn();
        void changeTurn();
        void clearBlocks();
        void calculateScore(int);
        int getStartLevel();
        void setStartLevel(int l);
        void setup();
        void reset();
        void triggerSpecialAction();
};

#endif
