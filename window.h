#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

class Xwindow {
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  //moved here so i can get it for events
  Display *d;
  Window w;
  Xwindow(); 
  void setup(int width, int height); // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  enum {White=0, Black, Red, Orange, Yellow, Green, Cyan, Blue, Purple}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  //draws the game board
  void drawBoard(deque<vector<char>> grid, int offsetx, int offsety, int squaresize);
  void drawInfo(int hiscore, int level1, int level2, int score1, int score2);
  void drawNextBlock(char blocktype, int squaresize, int x, int y);

  void blind(int player);
};

#endif
