#ifndef __TRIANGLE__
#define __TRIANGLE__

// this is the triangle discussed in Section 19.3

#include "GeometricObject.h"
#include "BBox.h"

class Triangle: public GeometricObject {	
	public:
	
		Triangle(void);   												
				
		Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

		virtual Triangle* 												
		clone(void) const;
	
		Triangle(const Triangle& triangle); 							

		~Triangle(void);   											

		Triangle& 														
		operator= (const Triangle& rhs);

		void 
		compute_normal(void);

		BBox
			get_bounding_box(void);
		
		virtual bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;		 					 
		
		virtual bool 																						 
		shadow_hit(const Ray& ray, double& tmin) const; 
		
		void set_origin(const double x, const double y, const double z);

		void set_normal(const double x, const double y, const double z);

	
		Point3D	v0, v1, v2;
		const Point3D firstPos_v0, firstPos_v1, firstPos_v2;
		Normal	normal;
};

inline void
Triangle::set_origin(const double x, const double y, const double z) {
	Point3D origin = Point3D(x, y, z);
	v0 = origin + firstPos_v0;
	v1 = origin + firstPos_v1;
	v2 = origin + firstPos_v2;
}

inline void
Triangle::set_normal(const double x, const double y, const double z) {
	Point3D origin = Point3D(x, y, z);
	v0 = origin + v0;
	v1 = origin + v1;
	v2 = origin + v2;
}


/*inline void
Triangle::set_origin(const double x, const double y, const double z) {
	p0.x = x;
	p0.y = y;
	p0.z = z;
}*/

#endif

