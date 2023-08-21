#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow() {}

void Xwindow::setup(int width, int height){
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[9][10]={"white", "black", "red", "orange", "yellow", "green", "cyan","blue", "purple"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 9; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

//need to call twice - once for each player's board
//offsets control where the top left corner of the board will be
void Xwindow::drawBoard(deque<vector<char>> grid, int offsetx, int offsety, int squaresize){
  int colour;
  //background colour
  fillRectangle(offsetx, offsety, 11*squaresize, 18*squaresize, Xwindow::Black);

  //draws the blocks
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
        /*colours for each block:
          I cyan 6
          J blue 7
          L orange 3
          O yellow 4
          S green 5 
          Z red 2
          T purple 8
        */

        if (grid[i][j] == 'I') {
          colour = Xwindow::Cyan;
        }
        else if (grid[i][j] == 'J') {
          colour = Xwindow::Blue;
        } 
        else if (grid[i][j] == 'L') {
          colour = Xwindow::Orange;
        } 
        else if (grid[i][j] == 'O') {
          colour = Xwindow::Yellow;
        } 
        else if (grid[i][j] == 'S') {
          colour = Xwindow::Green;
        } 
        else if (grid[i][j] == 'Z') {
          colour = Xwindow::Red;
        } 
        else if (grid[i][j] == 'T') {
          colour = Xwindow::Purple;
        }
        else{
          continue;
        }

        fillRectangle(offsetx + j*squaresize, offsety + i*squaresize, squaresize, squaresize, colour);
    }
  }

  //horizontal lines
  for (int i =0; i < 18; i++){
    XDrawLine(d, w, DefaultGC(d, s), offsetx, i*squaresize + offsety, offsetx + 11*squaresize, i*squaresize + offsety);
  }
  for (int j = 0; j < 11; j++){
    XDrawLine(d, w, DefaultGC(d, s), offsetx + j*squaresize, offsety, offsetx + j*squaresize, offsety + 18*squaresize);
  }
}

//displays player scores, level, hiscore
void Xwindow::drawInfo(int hiscore, int level1, int level2, int score1, int score2){
  fillRectangle(0, 0, 500, 50, Xwindow::White);
  drawString(20, 10, "Highscore: " + to_string(hiscore));
  drawString(20, 20, "PLAYER 1");
  drawString(260, 20, "PLAYER 2");
  drawString(20, 30, "Level: " + to_string(level1));
  drawString(260, 30, "Level: " + to_string(level2));
  drawString(20, 40, "Score: " + to_string(score1));
  drawString(260, 40, "Score: " + to_string(score2));
};

void Xwindow::drawNextBlock(char blocktype, int squaresize, int x, int y){
  int colour;
  fillRectangle(x, y, squaresize*4, squaresize*4, Xwindow::White);
  drawString(x, y, "Next Block: ");
  y+= 20;

  if (blocktype == 'I') {
    colour = Xwindow::Cyan;
    fillRectangle(x, y, squaresize*4, squaresize, colour);
  }
  else if (blocktype == 'J') {
    colour = Xwindow::Blue;
    fillRectangle(x, y, squaresize, squaresize, colour);
    fillRectangle(x, y + squaresize, squaresize*3, squaresize, colour);
  } 
  else if (blocktype == 'L') {
    colour = Xwindow::Orange;
    fillRectangle(x + squaresize, y, squaresize, squaresize, colour);
    fillRectangle(x, y + squaresize, squaresize*3, squaresize, colour);
  } 
  else if (blocktype == 'O') {
    colour = Xwindow::Yellow;
    fillRectangle(x, y, squaresize*2, squaresize*2, colour);
  } 
  else if (blocktype == 'S') {
    colour = Xwindow::Green;
    fillRectangle(x + squaresize, y, squaresize*2, squaresize, colour);
    fillRectangle(x, y + squaresize, squaresize*2, squaresize, colour);
  } 
  else if (blocktype == 'Z') {
    colour = Xwindow::Red;
    fillRectangle(x, y, squaresize*2, squaresize, colour);
    fillRectangle(x + squaresize, y + squaresize, squaresize*2, squaresize, colour);
  } 
  else if (blocktype == 'T') {
    colour = Xwindow::Purple;
    fillRectangle(x + squaresize, y, squaresize, squaresize, colour);
    fillRectangle(x, y + squaresize, squaresize*3, squaresize, colour);
  }
}

void Xwindow::blind(int player){
  int offset = 0;
  if (player == 2){
    offset = 240;
  }
  fillRectangle(80 + offset, 100, 120, 180, Xwindow::White);
  drawString(100 + offset,120, "???");
}
