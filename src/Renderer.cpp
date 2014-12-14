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
  computeConstants();

#ifdef NB_THREADS
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
#else
  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      renderPixel(i, j);
    }
  }
#endif

  return _pixelGrid;
}

void Renderer::renderLine(int x) {
  for (int j=0; j<SCREEN_HEIGHT; j++) {
    renderPixel(x, j);
    _pixelGrid[x][j].r = _pixelGrid[x][j].r > 255.f ? 255.f : _pixelGrid[x][j].r < 0.f ? 0.f : _pixelGrid[x][j].r;
    _pixelGrid[x][j].g = _pixelGrid[x][j].g > 255.f ? 255.f : _pixelGrid[x][j].g < 0.f ? 0.f : _pixelGrid[x][j].g;
    _pixelGrid[x][j].b = _pixelGrid[x][j].b > 255.f ? 255.f : _pixelGrid[x][j].b < 0.f ? 0.f : _pixelGrid[x][j].b;
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
  const Object3D* object = 0x0;
  Vec3Df xOffset = _startX + float(x) * _stepX;

  Vec3Df yOffset = _startY + float(y) * _stepY;
  Ray ray(_camera->pos, _camera->dir + xOffset + yOffset);

#ifdef DISPLAY_LIGHTS_SOURCES
  // Display light sources as a sphere
  for (UInt i=0; i<_scene->getLights().size(); i++) {
    Light light = _scene->getLights()[i];
    Vec3Df intersectionPoint, intersectionNormal;
    if (ray.intersect(light.getPos(), 0.01f, intersectionPoint, intersectionNormal)) {
      _pixelGrid[x][y].r = 50;
      _pixelGrid[x][y].g = 0;
      _pixelGrid[x][y].b = 0;
      return;
    }
  }
#endif


  Vec3Df dirToLight;
  Vec3Df lightIntersectionPoint;
  Vec3Df lightIntersectionNormal;

  if (_scene->getIntersected(ray, intersectionPoint, intersectionNormal, object)) {
#ifdef ENABLE_SHADOW
    std::vector<Light> keptLights;
    for (UInt i=0; i<_scene->getLights().size(); i++) {
      dirToLight = _scene->getLights()[i].getPos() - intersectionPoint;
      dirToLight.normalize();
      Ray rayToLight(intersectionPoint + EPSILON * dirToLight, dirToLight);
      if (!_scene->isShadow(rayToLight, object)) {
        keptLights.push_back(_scene->getLights()[i]);
      }
    }
    if (keptLights.size() > 0) {
      BRDF::getColor(_camera->pos, intersectionPoint, intersectionNormal, object->getMaterial(), keptLights, c);
    }
#else
    if (_scene->getIntersected(ray, lightIntersectionPoint, lightIntersectionNormal, object)) {
      BRDF::getColor(_camera->pos, intersectionPoint, intersectionNormal, object->getMaterial(), _scene->getLights(), c);
    }
#endif
  }
  
  _pixelGrid[x][y].r = c[0];
  _pixelGrid[x][y].g = c[1];
  _pixelGrid[x][y].b = c[2];
}
