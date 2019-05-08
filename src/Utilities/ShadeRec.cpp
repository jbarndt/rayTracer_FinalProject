// this file contains the definition of the class ShadeRec

// there is no default constructor as the World reference has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "Constants.h"
#include "ShadeRec.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec()
	: 	hit_an_object(false),
		hit_point(),
		local_hit_point(),
		normal(),
		ray(),
		depth(0),
		t(0.0)
{}




// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: 	hit_an_object(sr.hit_an_object),
		hit_point(sr.hit_point),
		local_hit_point(sr.local_hit_point),
		normal(sr.normal),
		ray(sr.ray),
		depth(sr.depth),
		t(sr.t)
{}



		
		
						
		
