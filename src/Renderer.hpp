#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene3D.hpp"
#include "Types.hpp"
#include "Vec3D.h"

class Renderer {
  public:
    Renderer(Scene3D* scene);
    ~Renderer();

  public:
    void setCamera(Vec3Df camPos, Vec3Df camDir, Vec3Df camRight, Vec3Df camUp);
    Pixel** render();

  private:
    void renderLine(int x);
    void renderPixel(int x, int y);

  private:
    Scene3D*    _scene;
    Pixel**     _pixelGrid;
    Vec3Df      _defaultColor;

    Vec3Df      _camPos;
    Vec3Df      _camDir;
    Vec3Df      _camRight;
    Vec3Df      _camUp;

  private:
    Vec3Df      _startX;
    Vec3Df      _stepX;
    Vec3Df      _startY;
    Vec3Df      _stepY;
};

#endif

