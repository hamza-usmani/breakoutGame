#include "SplashScreen.hpp"

SplashScreen::SplashScreen(int windowWidth, int windowHeight, int titlePaneHeight):windowWidth(windowWidth), windowHeight(windowHeight),titlePaneHeight(titlePaneHeight){
}

void SplashScreen::paint(XInfo &xinfo) { 
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[9], 0, 0, windowWidth, windowHeight/2 - titlePaneHeight);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[10], 0, windowHeight/2, windowWidth, windowHeight/2);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[6], 0, windowHeight/2 - titlePaneHeight, windowWidth, titlePaneHeight);

        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[6], sidebarWidth, windowHeight/6, name.c_str(), name.length());
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[6], sidebarWidth, windowHeight/5, id.c_str(), id.length());

        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/2.1, windowHeight/2 - titlePaneHeight/2, title.c_str(), title.length());

        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[6], windowWidth/2 - sidebarWidth, windowHeight/1.7, startgame.c_str(), startgame.length());
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[6], sidebarWidth, windowHeight/1.5, controls.c_str(), controls.length());
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[6], sidebarWidth  - sidebarWidth * 0.4, windowHeight/1.3, description.c_str(), description.length());
}
