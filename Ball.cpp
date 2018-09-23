#include "Ball.hpp"

Ball::Ball(float x, float y, float diameter, float dirX, float dirY): x(x), y(y), diameter(diameter), dirX(dirX), dirY(dirY) {}

void Ball::paint(XInfo &xinfo) {
    XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[11], x - diameter/2, y - diameter/2, diameter, diameter, 0, 360*64);
}

void Ball::setSpeed(int speed){
    dirX = speed;
    dirY = speed;
}

void Ball::increaseSpeed(){
    dirX = dirX/speed;
    dirY = dirY/speed;
    speed++;
    dirX *= speed;
    dirY *= speed;
}

void Ball::move(XInfo &xinfo, Paddle &paddle, Grid &grid){
    x = x + dirX;
    y = y + dirY;

    // Contact with the ground
    if (y + diameter/2 >= windowHeight){
        grid.youLose(xinfo);
    }

    // Contact with walls
    if (x + diameter/2 >=  gameWidth || x - diameter/2 <= 0) dirX = -dirX;
    if (y - diameter/2 <= 0) dirY = -dirY;

    // Contact with paddle
    if( (x + diameter/2 >= paddle.x || x - diameter/2 >= paddle.x) &&
        (x + diameter/2 <= paddle.x + paddle.width || x - diameter/2 <= paddle.x + paddle.width) && 
        (y + diameter/2 >= windowHeight-paddle.height ||  y + diameter/2 >= windowHeight-paddle.height)) {
            dirY = -dirY;
            y -=5; //tested with -=20
    }

    // Contact with block
    for (auto &row: grid.grid){
        for (auto &col: row){
            if ((x + diameter/2 >= col.x || x - diameter/2 >= col.x) && 
                (x + diameter/2 <= col.x + grid.blockWidth || x - diameter/2 <= col.x + grid.blockWidth) && 
                (y + diameter/2 >= col.y || y - diameter/2 >= col.y) && 
                (y + diameter/2 <= col.y + grid.blockHeight || y - diameter/2 <= col.y + grid.blockHeight) &&
                col.cellState != State::EMPTY){
                    col.blockHit(xinfo);
                    grid.blocksLeft--;
                    dirY = -dirY;
                    if (col.cellState == State::EMPTY){
                        score += 1;
                    } 
                    if (score % 5 == 0 && speed < 10){
                        increaseSpeed();
                    }
                }
        }
    }
}