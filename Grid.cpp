#include "Grid.hpp"

Grid::Grid(int rows, int cols, const int width, const int height, bool random): rows(rows), cols(cols){
    blocksLeft = rows * cols;
    blockSpacing = 10;
    blockWidth = (width - ((cols + 1) * blockSpacing)) / cols;
    blockHeight = height/20;

    for (int i=0; i< rows; i++){
        std::vector<Cell> tmp;
        for (int j=0; j< cols; j++){
            if (random){
                Cell tmpCell = Cell(j*blockWidth + (j+1)*blockSpacing, i*blockHeight + i*blockSpacing, static_cast<State>(rand() % 5));
                tmp.emplace_back(tmpCell);
            }
            else if (basic) {
                Cell tmpCell = Cell(j*blockWidth + (j+1)*blockSpacing, i*blockHeight + i*blockSpacing, static_cast<State>(rand() % 4 + 1));
                tmp.emplace_back(tmpCell);
            }
            else{
                if (i == 0){
                    rows*=2; 
                } 
                if (i == j || cols - i == j || i + 1 == j || cols - i - 1 == j || i - 1 == j || cols - i + 1 == j) {
                    Cell tmpCell = Cell(j*blockWidth + (j+1)*blockSpacing, i*blockHeight + i*blockSpacing, static_cast<State>(rand() % 4 + 1));
                    tmp.emplace_back(tmpCell);
                }
                else {
                    Cell tmpCell = Cell(j*blockWidth + (j+1)*blockSpacing, i*blockHeight + i*blockSpacing, State::EMPTY);
                    tmp.emplace_back(tmpCell);
                }
            }
        }
        grid.emplace_back(tmp);
    }
}

void Grid::paintSidebar(XInfo &xinfo){
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[6], gameWidth, 0, sidebarWidth, windowHeight);

    string sidebarInst1 = "Every 5 points";
    string sidebarInst2 = "the speed of the";
    string sidebarInst3 = "ball increases!";

    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.05, "Score:", 6);
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.1, to_string(score).c_str(), to_string(score).length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[8], gameWidth + sidebarWidth * 0.2, windowHeight * 0.15, sidebarInst1.c_str(), sidebarInst1.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[8], gameWidth + sidebarWidth * 0.2, windowHeight * 0.18, sidebarInst2.c_str(), sidebarInst2.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[8], gameWidth + sidebarWidth * 0.2, windowHeight * 0.21, sidebarInst3.c_str(), sidebarInst3.length());
    
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.28, "Speed:", 6);
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.33, to_string(speed).c_str(), to_string(speed).length());

    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.40, "Level:", 6);
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.43, to_string(level).c_str(), to_string(level).length());

    if (!basic){
        string sidebarInst4 = "Remember:";
        string sidebarInst5 = "Red/blue blocks are";
        string sidebarInst6 = "extra hard to break";
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[8], gameWidth + sidebarWidth * 0.2, windowHeight * 0.49, sidebarInst4.c_str(), sidebarInst4.length());
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[8], gameWidth + sidebarWidth * 0.2, windowHeight * 0.52, sidebarInst5.c_str(), sidebarInst5.length());
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[8], gameWidth + sidebarWidth * 0.2, windowHeight * 0.55, sidebarInst6.c_str(), sidebarInst6.length());
    }

    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.3, windowHeight * 0.9, "FPS: ", 5);
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], gameWidth + sidebarWidth * 0.55, windowHeight * 0.9, to_string(FPS).c_str(), to_string(FPS).length());
}

void Grid::paint(XInfo &xinfo) {
    for (auto &i : grid){
        for (auto &j: i){
            if (j.cellState == State::RED){
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[2], j.x, j.y, blockWidth, blockHeight);
            }
            else if (j.cellState == State::LIGHTBLUE){
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[3], j.x, j.y, blockWidth, blockHeight);
            }
            else if (j.cellState == State::PURPLE){
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[4], j.x, j.y, blockWidth, blockHeight);
            }
            else if (j.cellState == State::YELLOW){
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[5], j.x, j.y, blockWidth, blockHeight);
            }
            else if  (j.cellState == State::DARKRED){
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[12], j.x, j.y, blockWidth, blockHeight);
            }
            else if  (j.cellState == State::DARKBLUE){
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[13], j.x, j.y, blockWidth, blockHeight);
            }
        }
    }
    paintSidebar(xinfo);
}

void Grid::youLose(XInfo &xinfo){
    gameOver = true;
}