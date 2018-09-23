#include "Paddle.hpp"

Paddle::Paddle(float x, float y, float width, float height): x(x), y(y), width(width), height(height){}

void Paddle::paint(XInfo &xinfo) {
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, y, width, height);
}

void Paddle::left() {
    if(x - paddleSpeed >= 0){
        x = x - paddleSpeed;
    }  
}

void Paddle::right() {
    if (x + width <= gameWidth){
        x = x + paddleSpeed;
    }
}