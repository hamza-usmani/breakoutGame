#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
#include "Xinfo.hpp"

class Displayable {
	public:
		virtual void paint(XInfo &xinfo) = 0;	
};
#endif