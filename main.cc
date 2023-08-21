#include <iostream>
#include <sstream>
#include <cstring>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[]) {
    string input;
    string filename1 = "sequence1.txt";
    string filename2 = "sequence2.txt";
    bool graphics = true;
    Xwindow w;
    Controller game{0, 0};

    //CLI commands
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i],"-startlevel") == 0) {
            game.setStartLevel(stoi(argv[i+1]));
            game.setLevel1(stoi(argv[i+1])); 
            game.setLevel2(stoi(argv[i+1]));
        }
        else if (strcmp(argv[i], "-scriptfile1") == 0){
            filename1 = argv[i+1];
        }
        else if (strcmp(argv[i],"-scriptfile2") == 0){
            filename2 = argv[i+1];
        }
        else if (strcmp(argv[i],"-text") == 0){
            graphics = false;
        }
    }

    game.readscriptfile1(filename1);
    game.readscriptfile2(filename2);
    
    game.setup();
    game.print();

    if (graphics == true){
        w.setup(500,500);
        game.drawGame(w);
    }
    
    //now process game commands:
    while (cin >> input){  
        game.processCommand(input);
        if (graphics == true){
            game.drawGame(w);
        }
    }
 
}
