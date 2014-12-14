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

# define MIN(a,b) (a < b ? a : b)
# define MAX(a,b) (a > b ? a : b)

bool Ray::intersect(const BoundingBox& bbox) const {
  const Vec3Df & minBb = bbox.getMin ();
  const Vec3Df & maxBb = bbox.getMax ();

  float tx1 = (minBb[0] - _origin[0])*_invDirection[0];
  float tx2 = (maxBb[0] - _origin[0])*_invDirection[0];

  float tmin = MIN(tx1, tx2);
  float tmax = MAX(tx1, tx2);

  float ty1 = (minBb[1] - _origin[1])*_invDirection[1];
  float ty2 = (maxBb[1] - _origin[1])*_invDirection[1];

  tmin = MAX(tmin, MIN(ty1, ty2));
  tmax = MIN(tmax, MAX(ty1, ty2));

  float tz1 = (minBb[2] - _origin[2])*_invDirection[2];
  float tz2 = (maxBb[2] - _origin[2])*_invDirection[2];

  tmin = MAX(tmin, MIN(tz1, tz2));
  tmax = MIN(tmax, MAX(tz1, tz2));

  /*
  float t = FLT_MAX;
  return tmax >= MAX(0.f, tmin) && tmin < t;
  */

  return tmax >= MAX(0.f, tmin);
}

// Moller-Trumbore intersection algorithm
// cf. http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool Ray::intersect(const Vec3Df v0, const Vec3Df v1, const Vec3Df v2,
                     float &oT, float &oU, float &oV) const {

  Vec3Df e1, e2, h, s, q;
  float det, inv_det;

  //Find vectors for two edges sharing V1
  e1 = v1 - v0;
  e2 = v2 - v0;

  //Begin calculating determinant - also used to calculate u parameter
  h = Vec3Df::crossProduct(_direction, e2);

  //if determinant is near zero, ray lies in plane of triangle
  det = Vec3Df::dotProduct(e1, h);

  //CULLING IS OFF
  if (det > -EPSILON && det < EPSILON) {
    return false;
  }

  inv_det = 1.f / det;

  //calculate distance from V1 to ray origin
  s = _origin - v0;
  oU = inv_det * Vec3Df::dotProduct(s, h);

  if (oU < .0f || oU > 1.f) {
    //The intersection lies outside of the triangle
    return false;
  }

  //Prepare to test v parameter
  q = Vec3Df::crossProduct(s, e1);

  //Calculate V parameter and test bound
  oV = inv_det * Vec3Df::dotProduct(_direction, q);
  if(oV < .0f || oU + oV > 1.f) {
    //The intersection lies outside of the triangle
    return false;
  }

  oT = inv_det * Vec3Df::dotProduct(e2, q);
  return oT > EPSILON;
}

