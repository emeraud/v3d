#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene3D.hpp"
#include "Types.hpp"
#include "Vec3D.h"

struct Camera {
  Vec3Df   pos;
  Vec3Df   dir;
  Vec3Df   up;
  Vec3Df   right;

  Camera() { }
  Camera(Vec3Df _pos) : pos(_pos) {
    dir = - pos;
    dir.getTwoOrthogonals(up, right);
    normalize();
  }
  Camera(Vec3Df _pos, Vec3Df _dir, Vec3Df _up, Vec3Df _right) : pos(_pos), dir(_dir), up(_up), right(_right) {
    normalize();
  }

  private:
    void normalize() {
      dir.normalize();
      up.normalize();
      right.normalize();
    }
};

class Renderer {
  public:
    Renderer(Scene3D* scene);
    ~Renderer();

  public:
    void setCamera(const Camera& camera);
    Pixel** render();

  private:
    void renderLine(int x);
    void renderPixel(int x, int y);

  private:
    Scene3D*    _scene;
    Camera      _camera;
    Pixel**     _pixelGrid;
    Vec3Df      _defaultColor;

  private:
    Vec3Df      _startX;
    Vec3Df      _stepX;
    Vec3Df      _startY;
    Vec3Df      _stepY;
};

#endif

