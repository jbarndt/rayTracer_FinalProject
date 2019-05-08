#include "Rectangle.h"
#include "../Utilities/Maths.h"


const double Rectangle_rt::kEpsilon = 0.001;

// ----------------------------------------------------------------  default constructor

Rectangle_rt::Rectangle_rt(void)
        : 	GeometricObject(),
        p0(-1, 0, -1),
        a(0, 0, 2),
		b(2, 0, 0),
        a_len_squared(4.0),
        b_len_squared(4.0),
        normal(0, 1, 0),
        area(4.0),
        inv_area(0.25)
	{}


// ----------------------------------------------------------------  constructor
// this constructs the normal

Rectangle_rt::Rectangle_rt(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
        :	GeometricObject(),
        p0(_p0),
        a(_a),
        b(_b),
        a_len_squared(a.len_squared()),
        b_len_squared(b.len_squared()),
        area(a.length() * b.length()),
        inv_area(1.0 / area)
{
    normal = a ^ b;
    normal.normalize();
}


// ----------------------------------------------------------------  constructor
// this has the normal as an argument

Rectangle_rt::Rectangle_rt(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
        :	GeometricObject(),
        p0(_p0),
        a(_a),
        b(_b),
        a_len_squared(a.len_squared()),
        b_len_squared(b.len_squared()),
        normal(n),
        area(a.length() * b.length()),
        inv_area(1.0 / area)
{
    normal.normalize();
}



// ---------------------------------------------------------------- clone

Rectangle_rt*
Rectangle_rt::clone(void) const {
    return (new Rectangle_rt(*this));
}


// ---------------------------------------------------------------- copy constructor

Rectangle_rt::Rectangle_rt(const Rectangle_rt& r)
        :	GeometricObject(r),
        p0(r.p0),
        a(r.a),
        b(r.b),
        a_len_squared(r.a_len_squared),
        b_len_squared(r.b_len_squared),
        normal(r.normal),
        area(r.area),
        inv_area(r.inv_area) {
   
}



// ---------------------------------------------------------------- assignment operator

Rectangle_rt&
Rectangle_rt::operator= (const Rectangle_rt& rhs) {
    if (this == &rhs)
        return (*this);

    GeometricObject::operator=(rhs);

    p0				= rhs.p0;
    a				= rhs.a;
    b				= rhs.b;
    a_len_squared	= rhs.a_len_squared;
    b_len_squared	= rhs.b_len_squared;
    area			= rhs.area;
    inv_area		= rhs.inv_area;
    normal			= rhs.normal;

   

    return (*this);
}


// ---------------------------------------------------------------- destructor

Rectangle_rt::~Rectangle_rt (void) {

  
}

//------------------------------------------------------------------ get_bounding_box

BBox
Rectangle_rt::get_bounding_box(void) {
    double delta = 0.0001;

    return(BBox(min(p0.x, p0.x + a.x + b.x) - delta, max(p0.x, p0.x + a.x + b.x) + delta,
                min(p0.y, p0.y + a.y + b.y) - delta, max(p0.y, p0.y + a.y + b.y) + delta,
                min(p0.z, p0.z + a.z + b.z) - delta, max(p0.z, p0.z + a.z + b.z) + delta));
}

int
Rectangle_rt::get_ax_vector(void) {
	return(a.x);
}

int
Rectangle_rt::get_ay_vector(void) {
	return(a.y);
}

int
Rectangle_rt::get_bx_vector(void) {
	return(b.x);
}

int
Rectangle_rt::get_by_vector(void) {
	return(b.y);
}


//------------------------------------------------------------------ hit

bool
Rectangle_rt::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

    double t = (p0 - ray.start) * normal / (ray.dir * normal);

    if (t <= kEpsilon)
        return (false);

    Point3D p = ray.start + t * ray.dir;
    Vector3D d = p - p0;

    double ddota = d * a;

    if (ddota < 0.0 || ddota > a_len_squared)
        return (false);

    double ddotb = d * b;

    if (ddotb < 0.0 || ddotb > b_len_squared)
        return (false);

    tmin 				= t;
    sr.normal 			= normal;
    sr.local_hit_point 	= p;

    return (true);
}


// ---------------------------------------------------------------- setSampler

/*void
Rectangle_rt::set_sampler(Sampler* sampler) {
    sampler_ptr = sampler;
}*/


// ---------------------------------------------------------------- sample
// returns a sample point on the rectangle_rt
/*
Point3D
Rectangle_rt::sample(void) {
    Point2D sample_point = sampler_ptr->sample_unit_square();
    return (p0 + sample_point.x * a + sample_point.y * b);
}
*/

//------------------------------------------------------------------ get_normal

Normal
Rectangle_rt::get_normal(const Point3D& p) {
    return (normal);
}


// ---------------------------------------------------------------- pdf

float
Rectangle_rt::pdf(ShadeRec& sr) {
    return (inv_area);
}





