#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Types.hpp"
#include "Vec3D.h"

class Scene3D;
class Camera;

class Renderer {
  public:
    Renderer(Scene3D* scene, Camera* camera);
    ~Renderer();

  public:
    Pixel** render();

  private:
    void computeConstants();
    void renderLine(int x);
    void renderPixel(int x, int y);

  private:
    Scene3D*    _scene;
    Camera*     _camera;
    Pixel**     _pixelGrid;
    Vec3Df      _defaultColor;

  private:
    Vec3Df      _startX;
    Vec3Df      _stepX;
    Vec3Df      _startY;
    Vec3Df      _stepY;
};

#endif

