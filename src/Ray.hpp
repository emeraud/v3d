#ifndef RAY_HPP
#define RAY_HPP

#define EPSILON 0.000001f

#include "Vec3D.h"

class BoundingBox;

class Ray {
  public:
    inline Ray () {}
    inline Ray (const Vec3Df & origin, const Vec3Df & direction)
        : origin (origin), direction (direction) {}
    inline virtual ~Ray () {}

  public:
    inline const Vec3Df & getOrigin () const { return origin; }
    inline Vec3Df & getOrigin () { return origin; }
    inline const Vec3Df & getDirection () const { return direction; }
    inline Vec3Df & getDirection () { return direction; }

  public:
    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;

    // ray-triangle: O + tD = (1 - u - v)V0 + uV1 + vV2
    bool intersect (const Vec3Df iV0, const Vec3Df iV1, const Vec3Df iV2,
                    float &oT, float &oU, float &oV) const;
    
  private:
    Vec3Df origin;
    Vec3Df direction;
};


#endif

