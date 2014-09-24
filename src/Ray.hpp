#define EPSILON 0.000001
#define BIGNUMBER 9999999999.f

#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <vector>

#include "Vec3D.h"

class BoundingBox;

class Ray {
public:
    inline Ray () {}
    inline Ray (const Vec3Df & origin, const Vec3Df & direction)
        : origin (origin), direction (direction) {}
    inline virtual ~Ray () {}

    inline const Vec3Df & getOrigin () const { return origin; }
    inline Vec3Df & getOrigin () { return origin; }
    inline const Vec3Df & getDirection () const { return direction; }
    inline Vec3Df & getDirection () { return direction; }

    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;

/*
    bool intersect (const Vec3Df iV0, const Vec3Df iV1, const Vec3Df iV2,
                    const Vec3Df iN0, const Vec3Df iN1, const Vec3Df iN2,
                    Vec3Df &oIntersectionPoint,
                    Vec3Df &oIntersectionNormal) const  ;
*/

    // ray-triangle: O + tD = (1 - u - v)V0 + uV1 + vV2
    bool intersect (const Vec3Df iV0, const Vec3Df iV1, const Vec3Df iV2,
                    float &oT, float &oU, float &oV) const;

//    bool intersect(const Object iObject, Vec3Df &oIntersectionPoint, Vec3Df &oIntersectionNormal) const;
    
private:
    Vec3Df origin;
    Vec3Df direction;
};


#endif

