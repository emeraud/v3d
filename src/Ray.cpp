// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Ray.hpp"
#include "Triangle.h"
#include "Vec3D.h"

#include "BoundingBox.hpp"

#include <math.h>
#include <algorithm>


#include <iostream>


using namespace std;

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;
/*
bool Ray::intersect(const Vec3Df iV0, const Vec3Df iV1, const Vec3Df iV2,
                     const Vec3Df iN0, const Vec3Df iN1, const Vec3Df iN2,
                     Vec3Df &oIntersectionPoint,
                     Vec3Df &oIntersectionNormal) const {
    double t,u,v;
    if(this->intersect(iV0, iV1, iV2, t, u, v))
    {
        oIntersectionPoint = (1-u-v)*iV0 + u*iV1 + v*iV2;
        oIntersectionNormal = (1-u-v)*iN0 + u*iN1 + v*iN2;
        oIntersectionNormal.normalize();

        return true;
    }

    return false;
}
*/
bool Ray::intersect(const Vec3Df iV0, const Vec3Df iV1, const Vec3Df iV2,
                     float &oT, float &oU, float &oV) const {

    Vec3Df edge1, edge2, tvec, pvec, qvec;
    float det, inv_det;

    edge1 = iV1 - iV0;
    edge2 = iV2 - iV0;

    pvec = Vec3Df::crossProduct(direction, edge2);
    det = Vec3Df::dotProduct(edge1, pvec);

    if(det<EPSILON) {
        return false;
    }

    tvec = origin - iV0;

    oU = Vec3Df::dotProduct(tvec, pvec);
    if(oU < .0f || oU > det) {
        return false;
    }

    qvec = Vec3Df::crossProduct(tvec, edge1);

    oV = Vec3Df::dotProduct(direction, qvec);
    if(oV < .0f || oU + oV > det) {
        return false;
    }

    oT = Vec3Df::dotProduct(edge2, qvec);
    inv_det = 1.f/det;

    oT *= inv_det;
    oU *= inv_det;
    oV *= inv_det;

    return true;

}

bool Ray::intersect(const BoundingBox & bbox, Vec3Df & intersectionPoint) const {
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    bool inside = true;
    unsigned int  quadrant[NUMDIM];
    register unsigned int i;
    unsigned int whichPlane;
    Vec3Df maxT;
    Vec3Df candidatePlane;
    
    for (i=0; i<NUMDIM; i++)
        if (origin[i] < minBb[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = minBb[i];
            inside = false;
        } else if (origin[i] > maxBb[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = maxBb[i];
            inside = false;
        } else	{
            quadrant[i] = MIDDLE;
        }

    if (inside)	{
        intersectionPoint = origin;
        return (true);
    }

    for (i = 0; i < NUMDIM; i++)
        if (quadrant[i] != MIDDLE && direction[i] !=0.)
            maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
        else
            maxT[i] = -1.;

    whichPlane = 0;
    for (i = 1; i < NUMDIM; i++)
        if (maxT[whichPlane] < maxT[i])
            whichPlane = i;

    if (maxT[whichPlane] < 0.) return (false);
    for (i = 0; i < NUMDIM; i++)
        if (whichPlane != i) {
            intersectionPoint[i] = origin[i] + maxT[whichPlane] *direction[i];
            if (intersectionPoint[i] < minBb[i] || intersectionPoint[i] > maxBb[i])
                return (false);
        } else {
            intersectionPoint[i] = candidatePlane[i];
        }
    return (true);			
}
