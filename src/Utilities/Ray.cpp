#include "Ray.h"

// ---------------------------------------------------------------- default constructor

Ray::Ray (void)
	: 	start(0.0), 
		dir(0.0, 0.0, 1.0) 
{}

Ray::Ray(double x, double y, double z) : start(x,y,z), dir(0.0, 0.0, 1.0) {}

// ---------------------------------------------------------------- constructor

Ray::Ray (const Point3D& origin, const Vector3D& dir)
	: 	start(origin), 
		dir(dir) 
{}

// ---------------------------------------------------------------- copy constructor

Ray::Ray (const Ray& ray)
	: 	start(ray.start), 
		dir(ray.dir) 
{}

// ---------------------------------------------------------------- assignment operator

Ray& 
Ray::operator= (const Ray& rhs) {
	
	if (this == &rhs)
		return (*this);
		
	start = rhs.start; 
	dir = rhs.dir; 

	return (*this);	
}

// ---------------------------------------------------------------- destructor

Ray::~Ray (void) {}



