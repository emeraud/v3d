#ifndef RAY_HPP
#define RAY_HPP

#include <cfloat>
#include "Vec3D.h"

#define EPSILON 0.000001f

class BoundingBox;

class Ray {
  public:
    inline Ray () {}
    inline Ray (const Vec3Df & origin, const Vec3Df & direction) : _origin (origin), _direction (direction) {
      _direction.normalize();
      float x = -EPSILON > _direction[0] && EPSILON < _direction[0] ? (_direction[0] > 0.f ? FLT_MAX : -FLT_MAX) : 1.f/_direction[0];
      float y = -EPSILON > _direction[1] && EPSILON < _direction[1] ? (_direction[1] > 0.f ? FLT_MAX : -FLT_MAX) : 1.f/_direction[1];
      float z = -EPSILON > _direction[2] && EPSILON < _direction[2] ? (_direction[2] > 0.f ? FLT_MAX : -FLT_MAX) : 1.f/_direction[2];
      _invDirection = Vec3Df(x,y,z);
      _dirMin = std::min(std::min(x,y),z);
      _dirMax = std::max(std::max(x,y),z);
      //std::cout << "inv=" << _invDirection << " _dirMin=" << _dirMin << " _dirMax=" << _dirMax << std::endl;
    }
    inline virtual ~Ray () {}

  public:
    inline const Vec3Df & getOrigin () const { return _origin; }
    inline Vec3Df & getOrigin () { return _origin; }
    inline const Vec3Df & getDirection () const { return _direction; }
    inline Vec3Df & getDirection () { return _direction; }

  public:
    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;
    bool intersect (const BoundingBox & bbox) const;

    // ray-triangle: O + tD = (1 - u - v)V0 + uV1 + vV2
    bool intersect (const Vec3Df iV0, const Vec3Df iV1, const Vec3Df iV2,
                    float &oT, float &oU, float &oV) const;
    
  private:
    Vec3Df _origin;
    Vec3Df _direction;
    Vec3Df _invDirection;
    float _dirMin;
    float _dirMax;
};


#endif

