#include "Renderer.hpp"

#include "Config.hpp"

#include "Scene3D.hpp"
#include "Object3D.hpp"
#include "Camera.hpp"

#include "Ray.hpp"
#include "BRDF.hpp"

#include "PixelBlock.hpp"
#include "Dispatcher.hpp"

Renderer::Renderer(Scene3D* scene, Camera* camera) : _scene(scene), _camera(camera) {
  renderByBlock = false;
}

Renderer::~Renderer() {
}

void Renderer::computeConstants() {
  float fov = tan(_camera->getFieldOfView());

  Vec3Df xVec = _camera->getAspectRatio() * fov * _camera->getRight();
  Vec3Df yVec = fov * _camera->getUp();

  _startX = -0.5f * xVec;
  _startY = -0.5f * yVec;

  _stepX = 1.f/float(SCREEN_WIDTH) * xVec;
  _stepY = 1.f/float(SCREEN_HEIGHT) * yVec;
}

void Renderer::renderPixel(int x, int y, Pixel& pixel) {
  if (!renderByBlock) {
    computeConstants(); // move to a global context
  }
  /* we aim:
    Vec3Df stepX = (float(i) - 0.5f * float(SCREEN_WIDTH))/float(SCREEN_WIDTH) * obsRight;
    Vec3Df stepY = (float(j) - 0.5f * float(SCREEN_HEIGHT))/float(SCREEN_HEIGHT) * obsUp;
    Ray ray(obsPos, obsDir + stepX + stepY);
  */

  Vec3Df c = _defaultColor;

  Vec3Df xOffset = _startX + float(x) * _stepX;
  Vec3Df yOffset = _startY + float(y) * _stepY;
  Vec3Df camDir = _camera->getDir() + xOffset + yOffset;
  camDir.normalize();
  _interContext.ray = Ray(_camera->getPos(), camDir);

#ifdef DISPLAY_LIGHTS_SOURCES
  // Display light sources as a sphere
  for (UInt i=0; i<_scene->getLights().size(); i++) {
    Light light = _scene->getLights()[i];
    Vec3Df intersectionPoint, intersectionNormal;
    if (_interContext.ray.intersect(light.getPos(), 0.01f, intersectionPoint, intersectionNormal)) {
      pixel.r = light.getColor()[0] * 255;
      pixel.g = light.getColor()[1] * 255;
      pixel.b = light.getColor()[2] * 255;
      return;
    }
  }
#endif



  if (_scene->getIntersected(_interContext)) {
#ifdef ENABLE_SHADOW
    std::vector<Light> keptLights;
    for (UInt i=0; i<_scene->getLights().size(); i++) {
      Vec3Df dirToLight = _scene->getLights()[i].getPos() - _interContext.point;
      float sqMaxLength = dirToLight.getSquaredLength();
      dirToLight.normalize();
      _interContext.ray = Ray(_interContext.point + EPSILON * dirToLight, dirToLight);
      if (!_scene->isShadow(_interContext, sqMaxLength)) {
        keptLights.push_back(_scene->getLights()[i]);
      }
    }
    if (keptLights.size() > 0) {
      BRDF::getColor(_camera->getPos(), _interContext.point, _interContext.normal, _interContext.object->getMaterial(), keptLights, c);
    }
#else
    BRDF::getColor(_camera->getPos(), _interContext.point, _interContext.normal, _interContext.object->getMaterial(), _scene->getLights(), c);
#endif
  }
  
  pixel.r = c[0];
  pixel.g = c[1];
  pixel.b = c[2];
}

void Renderer::renderLine(int x, Pixel** pixelGrid) {
  renderByBlock = true;
  computeConstants();
  for (int j=0; j<SCREEN_HEIGHT; j++) {
    Pixel& pixel = pixelGrid[x][j];
    renderPixel(x, j, pixel);
    pixel.r = pixel.r > 255.f ? 255.f : pixel.r < 0.f ? 0.f : pixel.r;
    pixel.g = pixel.g > 255.f ? 255.f : pixel.g < 0.f ? 0.f : pixel.g;
    pixel.b = pixel.b > 255.f ? 255.f : pixel.b < 0.f ? 0.f : pixel.b;
  }
  renderByBlock = false;
}

void Renderer::render(Dispatcher* dispatcher, Pixel** pixelGrid) {
  PixelBlock pixelBlock;
  pixelBlock._threadId = _threadId;
  while (dispatcher->getNextBlock(pixelBlock)) {
    int x=0, y=0;
    while (pixelBlock.getNext(x, y)) {
      renderPixel(x, y, pixelGrid[x][y]);
    }
  }
}

