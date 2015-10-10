#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "geo/Vec3D.h"

class Camera {
  public:
    Camera();
    Camera(Vec3Df pos, Vec3Df dir, Vec3Df up, Vec3Df right);

  public:
    Vec3Df getUp();
    Vec3Df getRight();
    Vec3Df getPos();
    Vec3Df getDir();
    float getFieldOfView();
    float getAspectRatio();

  public:
    void setUp(Vec3Df up);
    void setRight(Vec3Df right);
    void setPos(Vec3Df pos);
    void setDir(Vec3Df dir);
    void setFieldOfView(float fieldOfView);
    void setAspectRatio(float aspectRatio);

  private:
    Vec3Df   _pos;
    Vec3Df   _dir;
    Vec3Df   _up;
    Vec3Df   _right;

    float    _fieldOfView;
    float    _aspectRatio;
};

#endif
