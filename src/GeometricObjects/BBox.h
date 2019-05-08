#ifndef __BBOX__
#define __BBOX__

#include "Utilities/Constants.h"
#include "Utilities/Point3D.h"
#include "Utilities/Ray.h"

class BBox {
public:
    double x0, x1, y0, y1, z0, z1;

    BBox(void);

    BBox(	const double x0, const double x1,
          const double y0, const double y1,
          const double z0, const double z1);

    BBox(const Point3D p0, const Point3D p1);

    BBox(const BBox& bbox);

    BBox&
    operator= (const BBox& rhs);

    ~BBox(void);

    bool
    hit(const Ray& ray) const;

    bool
    inside(const Point3D& p) const;
};

#endif

