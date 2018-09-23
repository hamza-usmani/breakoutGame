#include "ChooseType.hpp"

ChooseType::ChooseType() {}

void ChooseType::paint(XInfo &xinfo) { 
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[9], 0, 0, windowWidth, windowHeight/1.5 - titlePaneHeight);
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[10], 0, windowHeight/1.5, windowWidth, windowHeight/2);
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[6], 0, windowHeight/1.5 - titlePaneHeight, windowWidth, titlePaneHeight);

    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[6], windowWidth/4.5, windowHeight - titlePaneHeight/2, instructions.c_str(), instructions.length());

    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/4, windowHeight/1.8 - titlePaneHeight/2, basic.c_str(), basic.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/7, windowHeight/1.6 - titlePaneHeight/2, basicDescription1.c_str(), basicDescription1.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/7, windowHeight/1.5 - titlePaneHeight/2, basicDescription2.c_str(), basicDescription2.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/7, windowHeight/1.4 - titlePaneHeight/2, basicDescription3.c_str(), basicDescription3.length());

    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/1.5, windowHeight/1.8 - titlePaneHeight/2, advanced.c_str(), advanced.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/1.8, windowHeight/1.6 - titlePaneHeight/2, advDescription1.c_str(), advDescription1.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/1.8, windowHeight/1.5 - titlePaneHeight/2, advDescription2.c_str(), advDescription2.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/1.8, windowHeight/1.4 - titlePaneHeight/2, advDescription3.c_str(), advDescription3.length());
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[7], windowWidth/1.8, windowHeight/1.3 - titlePaneHeight/2, advDescription4.c_str(), advDescription4.length());

    if (leftSelected){
        XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[11], windowWidth/3.8, windowHeight/2 - titlePaneHeight/2, 15, 15, 0, 360*64);
    }
    else {
        XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[11], windowWidth/1.45, windowHeight/2 - titlePaneHeight/2, 15, 15, 0, 360*64);
    }
}

void ChooseType::left(){
    leftSelected = true;
}

void ChooseType::right(){
    leftSelected = false;
}