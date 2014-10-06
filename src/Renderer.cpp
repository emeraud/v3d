#include "Renderer.hpp"

#include <thread>

#include "Config.hpp"
#include "Object3D.hpp"
#include "BRDF.hpp"

Renderer::Renderer(Scene3D* scene, Camera* camera) : _scene(scene), _camera(camera) {
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

void Renderer::computeConstants() {
  _startX = -0.5f * _camera->right;
  _startY = -0.5f * _camera->up;

  _stepX = 1.f/float(SCREEN_WIDTH) * _camera->right;
  _stepY = 1.f/float(SCREEN_HEIGHT) * _camera->up;

}

Pixel** Renderer::render() {
  std::cout << "Begin raytracing" << std::endl;
  computeConstants();
  std::thread threads[NB_THREADS];
  int nbBlocks = SCREEN_WIDTH / NB_THREADS;
  int currentLine = 0;

  for (int k=0; k<nbBlocks; k++) {
    for (int i=0; i<NB_THREADS; i++) {
      if (currentLine < SCREEN_WIDTH) {
        threads[i] = std::thread(&Renderer::renderLine, this, currentLine);
        currentLine++;
      }
    }

    for (int i=0; i<NB_THREADS; i++) {
      if (currentLine - (NB_THREADS - i) < SCREEN_WIDTH) {
        threads[i].join();
      }
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
  Ray ray(_camera->pos, _camera->dir + xOffset + yOffset);

  if (object->intersect(ray, intersectionPoint, intersectionNormal)) {
    BRDF::getColor(_camera->pos, intersectionPoint, intersectionNormal, object->getMaterial(), _scene->getLights(), c);
  }
  
  _pixelGrid[x][y].r = c[0];
  _pixelGrid[x][y].g = c[1];
  _pixelGrid[x][y].b = c[2];
}
