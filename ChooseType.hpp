#ifndef CHOOSETYPE_H
#define CHOOSETYPE_H

#include <string>
#include "Displayable.hpp"
#include "globals.hpp"

using namespace std;

class ChooseType : public Displayable {
    string instructions = "Use left/right arrows and press s key to start a Basic or Advanced game";
    string basic = "Basic";
    string advanced = "Advanced";

    string basicDescription1 = "A basic breakout game mode with the";
    string basicDescription2 = "speed of the ball starting very easy";
    string basicDescription3 = "and increasing with every 5 points";

    string advDescription1 = "An advanced breakout game mode with";
    string advDescription2 = "speed of the ball increasing every 5";
    string advDescription3 = "points, stronger bricks and a more";
    string advDescription4 = "difficult starting level";

    int titlePaneHeight = windowHeight/2.5;

    public:
    bool leftSelected = true;
    
    ChooseType();
    virtual void paint(XInfo &xinfo);
    void left();
    void right();
};

#endif