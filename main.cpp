//  Created by Hamza Usmani on 2018-09-18.
//  Copyright © 2018 Hamza Usmani. All rights reserved.

#include <iostream>
#include <list>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <string>
#include <sstream>

#include "Displayable.hpp"
#include "SplashScreen.hpp"
#include "ChooseType.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Grid.hpp"

using namespace std;

const int windowWidth = 1280;
const int windowHeight = 800;

const int gameWidth = 1100;
const int sidebarWidth = windowWidth - gameWidth;

const int paddleWidth = 100;
const int paddleHeight = 15;
const int paddleSpeed = 40;

const int initialRows = 5;
const int initialCols = 10;

int FPS = 60;
int speed = 2;
int bufferSize = 10;

bool splashScreen = true;
bool chooseType = false;
bool basic = true;
bool gameOver = false;
int score = 0;
int level = 1;


// splashscreen creation
SplashScreen splash = SplashScreen(windowWidth, windowHeight, windowHeight/6);

// choose screen
ChooseType chooser = ChooseType();

// ball postition, size, and velocity
Ball ball = Ball(gameWidth/2,windowHeight*0.625, 20, speed, speed);

// paddle creation
Paddle paddle = Paddle(gameWidth/2 - paddleWidth/4, windowHeight - paddleHeight, paddleWidth, paddleHeight);

// grid creation
Grid grid = Grid(initialRows, initialCols, gameWidth, windowHeight);

void restart(){
    splashScreen = true;
    chooseType = false;
    chooser.leftSelected = true;
    basic = true;
    gameOver = false;
    score = 0;
    speed = 2;
    splash = SplashScreen(windowWidth, windowHeight, windowHeight/6);
    ball = Ball(gameWidth/2,windowHeight*0.625, 20, 2, 2);
    paddle = Paddle(gameWidth/2 - paddleWidth/4, windowHeight - paddleHeight, paddleWidth, paddleHeight);
    grid = Grid(initialRows, initialCols, gameWidth, windowHeight);
}

void wonRound(){
    ball = Ball(gameWidth/2,windowHeight*0.625, 20, 2, 2);
    paddle = Paddle(gameWidth/2 - paddleWidth/4, windowHeight - paddleHeight, paddleWidth, paddleHeight);
    grid = Grid(rand() % 6 + 3, rand() % 12 + 7, gameWidth, windowHeight, true);
    level++;
    splashScreen = false;
    gameOver = false;
    speed = 2;
}

string loseString = "You lost! Press the r key to restart or q to quit";
void loseMessage(XInfo &xinfo){
     XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[6], windowWidth/4.5, windowHeight/3, gameWidth * 0.5, windowHeight/4);
     XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/4, windowHeight/2.2, loseString.c_str(), loseString.length());
}

// Error function to print errors and exit the program
void error(string e) {
    cerr << e <<endl;
    exit(-1);
}

// Get current time
unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void eventLoop(XInfo &xinfo){    
    XEvent event;

    // time of last window paint
	unsigned long lastRepaint = 0;
	XWindowAttributes w;
	XGetWindowAttributes(xinfo.display, xinfo.window, &w);

    int depth = DefaultDepth(xinfo.display, DefaultScreen(xinfo.display));
	xinfo.pixmap = XCreatePixmap(xinfo.display, xinfo.window, w.width, w.height, depth);

	while (true) {
		if (XPending(xinfo.display) > 0) { 
			XNextEvent( xinfo.display, &event ); 

			switch ( event.type ) {
                case KeyPress: // any keypress
                    KeySym key;
                    char text[10];
                    int i = XLookupString( (XKeyEvent*)&event, text, 10, &key, 0 );
                    if (i == 1 && text[0] == 'q' ) {
                        XCloseDisplay(xinfo.display);
                        exit(0);
                    }
                    if (splashScreen){
                        if (i == 1 && text[0] == 's') {
                            splashScreen = false;
                            chooseType = true;
                        }
                    }
                    else if (chooseType){
                        if (i == 1 && text[0] == 's') {
                            chooseType = false;
                            if (chooser.leftSelected) basic = true;
                            else{
                                basic = false;
                                grid = Grid(initialRows, initialCols, gameWidth, windowHeight);
                            } 
                        }
                        else if (XLookupKeysym(&event.xkey, 0) == XK_Left) {
                            chooser.left();
                        }
                        else if (XLookupKeysym(&event.xkey, 0) == XK_Right) {
                            chooser.right();
                        }
                    }
                    else if (gameOver){
                        if (i == 1 && text[0] == 'r') {
                            restart();
                        }
                    }
                    else {
                        if (XLookupKeysym(&event.xkey, 0) == XK_Left) {
                            paddle.left();
                        }
                        else if (XLookupKeysym(&event.xkey, 0) == XK_Right) {
                            paddle.right();
                        }
                    }
                }
		}
		unsigned long end = now();	// get time in microsecond

		if (end - lastRepaint > 1000000 / FPS) { 
			Pixmap pixmap;
            pixmap = xinfo.pixmap;
            XSetForeground(xinfo.display, xinfo.gc[0], WhitePixel(xinfo.display, DefaultScreen(xinfo.display)));
			XFillRectangle(xinfo.display, pixmap, xinfo.gc[0], 0, 0, w.width, w.height);

            if (splashScreen){
                splash.paint(xinfo);
            }
            else if (chooseType){
                chooser.paint(xinfo);
            }
            else{
                paddle.paint(xinfo);
                grid.paint(xinfo);
                ball.paint(xinfo);
                if (gameOver){
                   loseMessage(xinfo);
                }
                else if (grid.blocksLeft == 0){
                    wonRound();
                    continue;
                }
                else{
                    ball.move(xinfo, paddle, grid);
                }
            }
            // double buffering to reduce stuttering in graphics
            XCopyArea(xinfo.display, pixmap, xinfo.window, xinfo.gc[0], 0, 0, w.width, w.height, 0, 0);
			XFlush(xinfo.display);
			lastRepaint = now();
		}

		if (XPending(xinfo.display) == 0) {
			usleep(1000000 / FPS - (end - lastRepaint));
		}
	}
}

void initGraphics(XInfo &xinfo){
    xinfo.display = XOpenDisplay("");
	if (xinfo.display == NULL) exit (-1);

	int screennum = DefaultScreen(xinfo.display);
	long background = WhitePixel(xinfo.display, screennum);
	long foreground = BlackPixel(xinfo.display, screennum);

	xinfo.window = XCreateSimpleWindow(xinfo.display, DefaultRootWindow(xinfo.display), 10, 10, windowWidth, windowHeight, 2, foreground, background);
	XSelectInput(xinfo.display, xinfo.window,ButtonPressMask | KeyPressMask);
    
    // set screen size and disable resizing
    XSizeHints *hints;
    hints = XAllocSizeHints();
    hints->flags= USPosition | PPosition | PSize | PAspect | PMinSize | PMaxSize | PResizeInc | PBaseSize;
    hints->x = 10;
    hints->y = 10;
    hints->width = windowWidth;
    hints->height = windowHeight;
    hints->base_width = windowWidth;
    hints->base_height = windowHeight;
    XSetWMNormalHints(xinfo.display, xinfo.window, hints); 

	// create gcs for drawing
    Colormap colors = DefaultColormap(xinfo.display, xinfo.screen);

    int i = 0;
    XColor green;
	xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#90EE90", &green, &green);
    XSetForeground(xinfo.display, xinfo.gc[i], green.pixel );

    i=1;
    XColor blue;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#1E90FF", &blue, &blue);
    XSetForeground( xinfo.display, xinfo.gc[i], blue.pixel );

    i=2;
    XColor red;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#FF4500", &red, &red);
    XSetForeground( xinfo.display, xinfo.gc[i], red.pixel);

    i=3;
    XColor lightblue;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#87CEFA", &lightblue, &lightblue);
    XSetForeground( xinfo.display, xinfo.gc[i], lightblue.pixel );

    i=4;
    XColor purple;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#9370DB", &purple, &purple);
    XSetForeground( xinfo.display, xinfo.gc[i], purple.pixel );

    i=5;
    XColor yellow;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#F0E68C", &yellow, &yellow);
    XSetForeground( xinfo.display, xinfo.gc[i], yellow.pixel );

    i=6;
    XColor darkgrey;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#444444", &darkgrey, &darkgrey);
    XSetForeground( xinfo.display, xinfo.gc[i], darkgrey.pixel );
    // setting font
    Font font;
    font = XLoadFont(xinfo.display, "10x20");
    XSetFont(xinfo.display, xinfo.gc[i], font);

    i=7;
    XColor fontcolor;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#ffffff", &fontcolor, &fontcolor);
    XSetForeground( xinfo.display, xinfo.gc[i], fontcolor.pixel );
    // setting font
    font = XLoadFont(xinfo.display, "10x20");
    XSetFont(xinfo.display, xinfo.gc[i], font);

    i=8;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#ffffff", &fontcolor, &fontcolor);
    XSetForeground( xinfo.display, xinfo.gc[i], fontcolor.pixel );
    // setting font
    Font fontsmall;
    fontsmall = XLoadFont(xinfo.display, "7x13");
    XSetFont(xinfo.display, xinfo.gc[i], fontsmall);

    i=9;
    XColor splashblue;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#d9e6fc", &splashblue, &splashblue);
    XSetForeground( xinfo.display, xinfo.gc[i], splashblue.pixel );

    i=10;
    XColor splashdarkblue;
    xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#7d98c4", &splashdarkblue, &splashdarkblue);
    XSetForeground(xinfo.display, xinfo.gc[i], splashdarkblue.pixel );

    XMapRaised(xinfo.display, xinfo.window);
	XFlush(xinfo.display);

    i=11;
    XColor lightgreen;
	xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#b0f4bc", &lightgreen, &lightgreen);
    XSetForeground(xinfo.display, xinfo.gc[i], lightgreen.pixel );

    i=12;
    XColor darkred;
	xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#772e17", &darkred, &darkred);
    XSetForeground(xinfo.display, xinfo.gc[i], darkred.pixel );

    i=13;
    XColor darkblue;
	xinfo.gc[i] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XAllocNamedColor(xinfo.display, colors, "#161e7a", &darkblue, &darkblue);
    XSetForeground(xinfo.display, xinfo.gc[i], darkblue.pixel );
}

int main(int argc, char *argv[]) {
    XInfo xinfo = XInfo();
    if (argc == 2) {
        istringstream ss(argv[1]);
        ss >> FPS; 
    }
    else if(argc == 3) {
        istringstream ss(argv[1]);
        ss >> FPS;
        istringstream ss2(argv[2]);
        ss2 >> speed;
        ball.setSpeed(speed);
    }
    if (FPS < 10 || FPS > 60){
            error("FPS is out of range (10-60)");
    }
    if (speed < 1 || speed > 10){
            error("Speed is out of range (1-10)");
    }
    // Initialize graphics, window parameters/hints
    initGraphics(xinfo);

    // Run the event loop to constantly listen for input and repaint screen
    eventLoop(xinfo);

    // Close the display
	XCloseDisplay(xinfo.display);
}
