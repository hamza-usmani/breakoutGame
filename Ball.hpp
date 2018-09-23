#ifndef BALL_H
#define BALL_H

#include "Displayable.hpp"
#include "Grid.hpp"
#include "Paddle.hpp"

class Ball : public Displayable {
    public:
    float x;
    float y;
    float diameter;
    float dirX;
    float dirY;

    Ball(float x, float y, float diameter, float dirX, float dirY);
    void paint(XInfo &xinfo) override;
    void setSpeed(int speed);
    void increaseSpeed();
    void move(XInfo &xinfo, Paddle &paddle, Grid &grid);
};

#endif