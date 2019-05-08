// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the Pinhole class

//#include "Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <iostream>
#include <math.h>

// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)
        :	Camera(),
        dist(500.0),
		f(-700.0),
        zoom(1.0) {}


// ----------------------------------------------------------------------------- copy constructor

Pinhole::Pinhole(const Pinhole& c)
        : 	Camera(c),
        dist(c.dist),
		f(c.f),
        zoom(c.zoom) {}


// ----------------------------------------------------------------------------- clone

Camera*
Pinhole::clone(void) const {
    return (new Pinhole(*this));
}



// ----------------------------------------------------------------------------- assignment operator

Pinhole&
Pinhole::operator= (const Pinhole& rhs) {
    if (this == &rhs)
        return (*this);

    Camera::operator= (rhs);

    dist 		= rhs.dist;
    zoom	= rhs.zoom;

    return (*this);
}


// ----------------------------------------------------------------------------- destructor

Pinhole::~Pinhole(void) {}


// ----------------------------------------------------------------------------- get_direction

Vector3D
Pinhole::get_direction(const Point2D& p) const {
    Vector3D dir = p.x * u + p.y * v - dist * w;
	dir.normalize();
    return(dir);
}

// ----------------------------------------------------------------------------- get_direction

Vector3D
Pinhole::get_lens_direction(const Point2D& pp, const Point2D& lp) const {

	Point2D p;

	p.x = pp.x *  f / dist;
	p.y = pp.y * f / dist;


	Vector3D dir = (p.x - lp.x) * u + (p.y - lp.y) * v - f * w;
	dir.normalize();
	return(dir);
}



// ----------------------------------------------------------------------------- render_scene
/*
void
Pinhole::render_scene(const World& w) {
    RGBColor	L;
    //ViewPlane	vp(w.get_viewplane());
    Ray			ray;
    int 		depth = 0;
    Point2D 	pp;		// sample point on a pixel
    //const int   NUM_SAMPLES = vp.get_sampler()->get_bundle_size();
    int n = (int)sqrt((float)NUM_SAMPLES);
//    int n = (int)sqrt((float)vp.num_samples);

    float pix_size = vp.get_pixel_size() / zoom;
    ray.o = eye;

    for (int r = 0; r < vp.vres; r++)			// up
        for (int c = 0; c < vp.hres; c++) {		// across
            L = black;

            for (int p = 0; p < n; p++)			// up pixel
                for (int q = 0; q < n; q++) {	// across pixel
                    pp.x = pix_size * (c - 0.5 * vp.hres + (q + 0.5) / n);
                    pp.y = pix_size * (r - 0.5 * vp.vres + (p + 0.5) / n);
                    ray.d = get_direction(pp);
                    L += w.get_tracer()->trace_ray(ray, depth);
                }

            L /= NUM_SAMPLES;
            L *= exposure_time;
            w.display_pixel(r, c, L);
        }
}*/



