#include "Ray.hpp"
#include "Triangle.h"
#include "Vec3D.h"

#include "BoundingBox.hpp"

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;

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
    if (_origin[i] < minBb[i]) {
      quadrant[i] = LEFT;
      candidatePlane[i] = minBb[i];
      inside = false;
    } else if (_origin[i] > maxBb[i]) {
      quadrant[i] = RIGHT;
      candidatePlane[i] = maxBb[i];
      inside = false;
    } else	{
      quadrant[i] = MIDDLE;
    }

  if (inside)	{
    intersectionPoint = _origin;
    return (true);
  }

  for (i = 0; i < NUMDIM; i++)
    if (quadrant[i] != MIDDLE && _direction[i] !=0.)
      maxT[i] = (candidatePlane[i]-_origin[i]) / _direction[i];
    else
      maxT[i] = -1.;

  whichPlane = 0;
  for (i = 1; i < NUMDIM; i++)
    if (maxT[whichPlane] < maxT[i])
      whichPlane = i;

  if (maxT[whichPlane] < 0.) return (false);
  for (i = 0; i < NUMDIM; i++)
    if (whichPlane != i) {
      intersectionPoint[i] = _origin[i] + maxT[whichPlane] *_direction[i];
      if (intersectionPoint[i] < minBb[i] || intersectionPoint[i] > maxBb[i])
          return (false);
    } else {
      intersectionPoint[i] = candidatePlane[i];
    }

  return (true);			
}

bool Ray::intersect(const Vec3Df v0, const Vec3Df v1, const Vec3Df v2,
                     float &oT, float &oU, float &oV) const {

  Vec3Df e1, e2, h, s, q;
  float a, f;

  e1 = v1 - v0;
  e2 = v2 - v0;

  h = Vec3Df::crossProduct(_direction, e2);
  a = Vec3Df::dotProduct(e1, h);

  if (a > -EPSILON && a < EPSILON) {
    return false;
  }

  f = 1.f / a;
  s = _origin - v0;
  oU = f * Vec3Df::dotProduct(s, h);

  if (oU < .0f || oU > 1.f) {
    return false;
  }

  q = Vec3Df::crossProduct(s, e1);
  oV = f * Vec3Df::dotProduct(_direction, q);
  if(oV < .0f || oU + oV > 1.f) {
    return false;
  }

  oT = f * Vec3Df::dotProduct(e2, q);
  return oT > EPSILON;
}

