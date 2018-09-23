#ifndef PADDLE_H
#define PADDLE_H

#include "Displayable.hpp"
#include "globals.hpp"

class Paddle : public Displayable {
    public:
    float x;
    float y;
    float width;
    float height;

    Paddle(float x, float y, float width, float height);
    virtual void paint(XInfo &xinfo) override;
    void left();
    void right();
};

#endif