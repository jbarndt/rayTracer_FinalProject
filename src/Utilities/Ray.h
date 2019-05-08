#ifndef __RAY__
#define __RAY__

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
	public:
	
		Point3D			start;  	// starting point or tail of the ray. The book calls this o for origin.
		Vector3D		dir; 		  // direction 
		
		Ray(void);	
    Ray(double x, double y, double z);
		
		Ray(const Point3D& origin, const Vector3D& dir);	
		
		Ray(const Ray& ray); 		
		
		Ray& 						
		operator= (const Ray& rhs);
		 								
		~Ray(void);
};

#endif
