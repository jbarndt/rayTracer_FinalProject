#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "GeometricObject.h"
#include "BBox.h"

class Rectangle_rt: public GeometricObject {
public:

    Rectangle_rt(void);
    Rectangle_rt(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
    Rectangle_rt(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);

    virtual Rectangle_rt* clone() const;

    Rectangle_rt(const Rectangle_rt& r);

    virtual ~Rectangle_rt();

    Rectangle_rt& operator= (const Rectangle_rt& rhs);

    BBox get_bounding_box();

	int get_ax_vector();
	int get_ay_vector();

	int get_bx_vector();
	int get_by_vector();

    virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;


    // the following functions are used when the rectangle is a light source
    //virtual Point3D sample();

    virtual Normal get_normal(const Point3D& p);

    virtual float pdf(ShadeRec& sr);

	void set_origin(const Point3D& c);

	void set_origin(const double x, const double y, const double z);

private:

    Point3D 		p0;   			// corner vertex
    Vector3D		a;				// side
    Vector3D		b;				// side
    double			a_len_squared;	// square of the length of side a
    double			b_len_squared;	// square of the length of side b
    Normal			normal;

    float			area;			// for rectangular lights
    float			inv_area;		// for rectangular lights

    static const double kEpsilon;
};

inline void
Rectangle_rt::set_origin(const Point3D& c) {
	p0 = c;
}

inline void
Rectangle_rt::set_origin(const double x, const double y, const double z) {
	p0.x = x;
	p0.y = y;
	p0.z = z;
}

#endif
