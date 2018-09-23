#ifndef GRID_H
#define GRID_H

#include <vector>
#include <stdlib.h>
#include <string> 
#include "Displayable.hpp"
#include "globals.hpp"

using namespace std;

enum State{EMPTY, RED, LIGHTBLUE, PURPLE, YELLOW, DARKRED, DARKBLUE};

class Cell{
    public:
    int x;
    int y;
    State cellState;

    Cell(int x, int y, State cellState): x(x), y(y), cellState(cellState) {}

    void blockHit(XInfo &xinfo){
        if (basic) {
            cellState = State::EMPTY;
        }
        else {
            if (cellState == State::PURPLE || cellState == State::YELLOW || cellState == State::DARKRED || cellState == State::DARKBLUE){
                cellState = State::EMPTY; 
            }
            else if (cellState == State::RED){
                cellState = State::DARKRED;
            }
            else if (cellState == State::LIGHTBLUE){
                cellState = State::DARKBLUE;
            }
        }
    }
};

class Grid : public Displayable {
    public:
    vector<vector<Cell> > grid;
    int rows;
    int cols;
    int blocksLeft;

    int blockWidth;
    int blockHeight;
    int blockSpacing;

    Grid(int rows, int cols, const int width, const int height, bool random = false);
    void paintSidebar(XInfo &xinfo);
    virtual void paint(XInfo &xinfo) override;
    void youLose(XInfo &xinfo);
};

#endif