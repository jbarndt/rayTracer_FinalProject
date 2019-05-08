
#include "../Utilities/Constants.h"
#include "Triangle.h"
#include "BBox.h"
#include "../Utilities/Maths.h"

// ----------------------------------------------------------------  default constructor

Triangle::Triangle(void)
	: GeometricObject(),
	v0(0, 0, -5),
	v1(0, 5, -5),
	v2(5, 0, -5),
	firstPos_v0(v0),
	firstPos_v1(v1),
	firstPos_v2(v2),
	normal(0, 0, 1)
{}

// ---------------------------------------------------------------- constructor

Triangle::Triangle (const Point3D& a, const Point3D& b, const Point3D& c)
	: 	GeometricObject(),
		v0(a),
		v1(b),
		v2(c),
	firstPos_v0(v0),
	firstPos_v1(v1),
	firstPos_v2(v2)
{
	compute_normal();	
}


// ---------------------------------------------------------------- clone

Triangle* 
Triangle::clone(void) const {
	return (new Triangle(*this));
}


// ---------------------------------------------------------------- copy constructor

Triangle::Triangle (const Triangle& triangle)
	:	GeometricObject(triangle),
		v0(triangle.v0),
		v1(triangle.v1),
		v2(triangle.v2),
		normal(triangle.normal)
{}


// ---------------------------------------------------------------- assignment operator

Triangle& 
Triangle::operator= (const Triangle& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	v0 		= rhs.v0;
	v1 		= rhs.v1;
	v2 		= rhs.v2;
	normal 	= rhs.normal;
		
	return (*this);
}


// ---------------------------------------------------------------- destructor

Triangle::~Triangle (void) {}



// ---------------------------------------------------------------- compute_normal

void 
Triangle::compute_normal(void) {
	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}


BBox
Triangle::get_bounding_box(void) {
	double delta = 0.000001; 
	
	return (BBox(min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta, 
				 min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta, 
				 min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta));
}


// ------------------------------------------------------------------------------ hit

bool 
Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	

	double a =  v0.x - v1.x, b =  v0.x - v2.x, c = ray.dir.x, d = v0.x - ray.start.x;
	double e =  v0.y - v1.y, f =  v0.y - v2.y, g = ray.dir.y, h = v0.y - ray.start.y;
	double i =  v0.z - v1.z, j =  v0.z - v2.z, k = ray.dir.z, l = v0.z - ray.start.z;
	
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon) 
		return (false);
					
	tmin 				= t;
	sr.normal 			= normal;  	
	sr.local_hit_point 	= ray.start + t * ray.dir;	
	
	return (true);	
}  		


// ------------------------------------------------------------------------------ shadow_hit

bool 																						 
Triangle::shadow_hit(const Ray& ray, double& tmin) const {	
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.dir.x, d = v0.x - ray.start.x; 
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.dir.y, h = v0.y - ray.start.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.dir.z, l = v0.z - ray.start.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0)
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon)
		return (false);
					
	tmin = t;
	
	return(true);	
}  

