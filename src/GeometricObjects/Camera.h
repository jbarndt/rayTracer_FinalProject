/*
Vector3 position
Vector3 viewDirection
Vector3 upVector (0,1,0)
double viewDistance or double angleOfView (In the vertical view plane)
double nearClipDistance
double farClipDistance
*/

#ifndef __CAMERA__
#define __CAMERA__

#include "../Utilities/Point3D.h"
#include "../Utilities/Point2D.h"
#include "../Utilities/Vector3D.h"

//--------------------------------------------------------------------- class Camera

class Camera {
public:

	Camera();   							// default constructor

	Camera(const Camera& camera);			// copy constructor

	virtual Camera*							// virtual copy constructor
		clone(void) const = 0;

	Camera&
		operator= (const Camera& rhs);

	//virtual
	//	~Camera();

	/*virtual void
		render_scene();*/

	Point3D get_eye(void);

	void
		set_eye(const Point3D& p);

	void
		set_eye(const float x, const float y, const float z);

	void
		set_lookat(const Point3D& p);

	void
		set_lookat(const float x, const float y, const float z);

	void
		set_up_vector(const Vector3D& u);

	void
		set_up_vector(const float x, const float y, const float z);

	void
		set_roll(const float ra);

	void
		set_exposure_time(const float exposure);

	Point3D
		get_lens_origin(const float x, const float y);

	void 
		compute_uvw(void);


protected:

	Point3D			eye;				// eye point
	Point3D			lookat; 			// lookat point
	float			ra;					// roll angle
	Vector3D		u, v, w;			// orthonormal basis vectors
	Vector3D		up;					// up vector
	float			exposure_time;

};


// inlined access functions

inline Point3D
Camera::get_eye(void) {
	return(eye);
}

// ----------------------------------------------------------------- set_eye

inline void
Camera::set_eye(const Point3D& p) {
	eye = p;
}


// ----------------------------------------------------------------- set_eye

inline void
Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x;
	eye.y = y;
	eye.z = z;
}


// ----------------------------------------------------------------- set_lookat

inline void
Camera::set_lookat(const Point3D& p) {
	lookat = p;
}


// ----------------------------------------------------------------- set_lookat

inline void
Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x;
	lookat.y = y;
	lookat.z = z;
}


// ----------------------------------------------------------------- set_up_vector

inline void
Camera::set_up_vector(const Vector3D& u) {
	up = u;
}


// ----------------------------------------------------------------- set_up_vector

inline void
Camera::set_up_vector(const float x, const float y, const float z) {
	up.x = x;
	up.y = y;
	up.z = z;
}


// ----------------------------------------------------------------- set_roll

inline void
Camera::set_roll(const float r) {
	ra = r;
}


// ----------------------------------------------------------------- set_exposure_time

inline void
Camera::set_exposure_time(const float exposure) {
	exposure_time = exposure;
}


#endif
