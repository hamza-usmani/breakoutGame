#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <string>
#include "Displayable.hpp"

using namespace std;

class SplashScreen : public Displayable {
    string name = "Hamza Usmani";
    string id = "20617233";
    string title = "BREAKOUT";
    string description = "Break the blocks on the board with a ball by bounching it off your paddle. Don't let the ball hit the floor!";
    string controls = "Use the left and right arrow keys to move your paddle. Press the q key at any time to quit";
    string startgame = "Press the s key to start the game";
    int titlePaneHeight;
    int windowWidth;
    int windowHeight;

    public:
    SplashScreen(int windowWidth, int windowHeight, int titlePaneHeight);
    void paint(XInfo &xinfo) override;
};

#endif