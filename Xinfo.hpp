#ifndef XINFO_H
#define XINFO_H
// Header files for X functions
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include "globals.hpp"

struct XInfo {
    int screen;
    int width;
    int height;
    
    Display* display;
    Pixmap pixmap;
    Window window;
    GC gc[14]; 

    XInfo(){
        display =  XOpenDisplay("");
        if (display == NULL) exit (-1);

        int screennum = DefaultScreen(display);
        long background = WhitePixel(display, screennum);
        long foreground = BlackPixel(display, screennum);
        screen = screennum;

        window = XCreateSimpleWindow(display, DefaultRootWindow(display), 10, 10, windowWidth, windowHeight, 2, foreground, background);

        XWindowAttributes w;
	    XGetWindowAttributes(display, window, &w);

        int depth = DefaultDepth(display, DefaultScreen(display));
        pixmap = XCreatePixmap(display, window, w.width, w.height, depth);

        for (int i=0; i<14; ++i){
            gc[i] = XCreateGC(display, window, 0, 0);
        }
    }
};

#endif