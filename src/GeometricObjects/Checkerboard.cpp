#include "Checkerboard.h"
#include <cmath>   

ofColor WHITE_TILE = ofColor(255, 255, 255);
ofColor BLACK_TILE = ofColor(0, 0, 0);


// ----------------------------------------------------------------------  default constructor

Checkerboard::Checkerboard(void)
	: Plane()
{}


// ----------------------------------------------------------------------  constructor
/*
Plane::Plane(const Point3D& point, const Normal& normal)
	
{
	n.normalize();
}*/


// ---------------------------------------------------------------- copy constructor

Checkerboard::Checkerboard(const Checkerboard& checkerboard)
	: Plane(checkerboard)
{}


// ---------------------------------------------------------------- assignment operator

Checkerboard&
Checkerboard::operator= (const Checkerboard& rhs) {

	if (this == &rhs)
		return (*this);

	Plane::operator= (rhs);

	return (*this);
}


// ---------------------------------------------------------------- destructor

Checkerboard::~Checkerboard(void)
{}

// return true if white, return false if black 
bool
Checkerboard :: getColor(double x, double y, double z)
{
	//std::cout << x << ", " << z << " | " << abs((int)(floor(x))) % 2 << ", " << abs((int)(floor(z))) % 2 << "\n";
	
	if (abs((int)(floor(x))) % 2 == abs((int)(floor(z))) % 2)
		return true;
	return false;
}