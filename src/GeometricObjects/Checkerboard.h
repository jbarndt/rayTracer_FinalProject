#ifndef __CHECKERBOARD__
#define __CHECKERBOARD__

// checkerboard class
#include "ofColor.h"
#include "Plane.h"

class Checkerboard: public Plane {

public:

	Checkerboard(void);									// default constructor

	Checkerboard(const Checkerboard& ch);						// copy constructor

	~Checkerboard(void);									// destructor

	Checkerboard& 										// assignment operator
		operator= (const Checkerboard& rhs);

	bool
	getColor(double x, double y, double z);
};


#endif


