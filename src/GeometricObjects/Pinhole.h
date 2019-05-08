#ifndef __PINHOLE__
#define __PINHOLE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class Pinhole

#include "../Utilities/Point2D.h"
#include "Camera.h"

//--------------------------------------------------------------------- class Pinhole

class Pinhole: public Camera {
public:

    Pinhole();

    Pinhole(const Pinhole& ph);

    virtual Camera*
    clone(void) const;

    Pinhole&
    operator= (const Pinhole& rhs);

    virtual
    ~Pinhole();

    void
    set_view_distance(const float vpd);

    void
    set_zoom(const float zoom_factor);

    Vector3D
    get_direction(const Point2D& p) const;

	Vector3D
		get_lens_direction(const Point2D& pp, const Point2D& lp) const;

   // virtual void render_scene();

    float	dist;		// view plane distance
	float	f;		// focal plane distance
    float	zoom;	// zoom factor

};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(float _dist) {
    dist = _dist;
}



//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(float zoom_factor) {
    zoom = zoom_factor;
}

#endif

