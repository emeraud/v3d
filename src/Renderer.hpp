#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Types.hpp"
#include "Vec3D.h"

class Scene3D;
class Camera;

/* Thread safe rendering class */
class Renderer {
  public:
    Renderer(Scene3D* scene, Camera* camera);
    ~Renderer();

  public:
    void renderPixel(int x, int y, Pixel& pixel);
    void renderLine(int x, Pixel** pixelGrid);

  private:
    void computeConstants();

  private:
    Scene3D*    _scene;
    Camera*     _camera;
    Vec3Df      _defaultColor;

  private:
    Vec3Df      _startX;
    Vec3Df      _stepX;
    Vec3Df      _startY;
    Vec3Df      _stepY;
};

#endif

