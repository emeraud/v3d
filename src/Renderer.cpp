#include "Renderer.hpp"

#include <thread>

#include "Config.hpp"
#include "Object3D.hpp"
#include "BRDF.hpp"

Renderer::Renderer(Scene3D* scene) : _scene(scene) {
  _pixelGrid = new Pixel*[SCREEN_WIDTH];
  for (int i=0; i<SCREEN_WIDTH; i++) {
    _pixelGrid[i] = new Pixel[SCREEN_HEIGHT];
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      _pixelGrid[i][j].r = 0;
      _pixelGrid[i][j].g = 0;
      _pixelGrid[i][j].b = 0;
    }
  }
}

Renderer::~Renderer() {
  for (int i=0; i<SCREEN_WIDTH; i++) {
    delete[] _pixelGrid[i];
  }
  delete[] _pixelGrid;
}

void Renderer::setCamera(const Camera& camera) {
  _camera = camera;

  _startX = -0.5f * camera.right;
  _startY = -0.5f * camera.up;

  _stepX = 1.f/float(SCREEN_WIDTH) * camera.right;
  _stepY = 1.f/float(SCREEN_HEIGHT) * camera.up;
}

Pixel** Renderer::render() {
  std::cout << "Begin raytracing" << std::endl;
  std::thread threads[4];
  for (int k=0; k<160; k++) {
    for (int i=0; i<4; i++) {
      threads[i] = std::thread(&Renderer::renderLine, this, 4*k + i);
    }

    for (int i=0; i<4; i++) {
      threads[i].join();
    }
  }

  std::cout << "End raytracing" << std::endl;

  return _pixelGrid;
}

void Renderer::renderLine(int x) {
  for (int j=0; j<SCREEN_HEIGHT; j++) {
    renderPixel(x, j);
  }
}

void Renderer::renderPixel(int x, int y) {
  /* we aim:
    Vec3Df stepX = (float(i) - 0.5f * float(SCREEN_WIDTH))/float(SCREEN_WIDTH) * obsRight;
    Vec3Df stepY = (float(j) - 0.5f * float(SCREEN_HEIGHT))/float(SCREEN_HEIGHT) * obsUp;
    Ray ray(obsPos, obsDir + stepX + stepY);
  */

  Vec3Df intersectionPoint;
  Vec3Df intersectionNormal;
  Vec3Df c = _defaultColor;
  const Object3D* object = _scene->getObjects()[0];
  Vec3Df xOffset = _startX + float(x) * _stepX;

  Vec3Df yOffset = _startY + float(y) * _stepY;
  Ray ray(_camera.pos, _camera.dir + xOffset + yOffset);

  if (object->intersect(ray, intersectionPoint, intersectionNormal)) {
    BRDF::getColor(_camera.pos, intersectionPoint, intersectionNormal, object->getMaterial(), _scene->getLights(), c);
  }
  
  _pixelGrid[x][y].r = c[0];
  _pixelGrid[x][y].g = c[1];
  _pixelGrid[x][y].b = c[2];
}
