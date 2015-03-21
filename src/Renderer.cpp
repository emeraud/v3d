#include "Renderer.hpp"

#include "Config.hpp"

#include "Scene3D.hpp"
#include "Object3D.hpp"
#include "Camera.hpp"

#include "Ray.hpp"
#include "BRDF.hpp"

Renderer::Renderer(Scene3D* scene, Camera* camera) : _scene(scene), _camera(camera) {
  std::cout << "Creating renderer" << std::endl;
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
  computeConstants(); // move to a global context
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
  Vec3Df camDir = _camera->getDir() + xOffset + yOffset;
  camDir.normalize();
  Ray ray(_camera->getPos(), camDir);

#ifdef DISPLAY_LIGHTS_SOURCES
  // Display light sources as a sphere
  for (UInt i=0; i<_scene->getLights().size(); i++) {
    Light light = _scene->getLights()[i];
    Vec3Df intersectionPoint, intersectionNormal;
    if (ray.intersect(light.getPos(), 0.01f, intersectionPoint, intersectionNormal)) {
      pixel.r = 50;
      pixel.g = 0;
      pixel.b = 0;
      return;
    }
  }
#endif



  if (_scene->getIntersected(ray, intersectionPoint, intersectionNormal, object)) {
#ifdef ENABLE_SHADOW
    std::vector<Light> keptLights;
    for (UInt i=0; i<_scene->getLights().size(); i++) {
      Vec3Df dirToLight = _scene->getLights()[i].getPos() - intersectionPoint;
      float sqMaxLength = dirToLight.getSquaredLength();
      dirToLight.normalize();
      Ray rayToLight(intersectionPoint + EPSILON * dirToLight, dirToLight);
      if (!_scene->isShadow(rayToLight, object, sqMaxLength)) {
        keptLights.push_back(_scene->getLights()[i]);
      }
    }
    if (keptLights.size() > 0) {
      BRDF::getColor(_camera->getPos(), intersectionPoint, intersectionNormal, object->getMaterial(), keptLights, c);
    }
#else
    BRDF::getColor(_camera->getPos(), intersectionPoint, intersectionNormal, object->getMaterial(), _scene->getLights(), c);
#endif
  }
  
  pixel.r = c[0];
  pixel.g = c[1];
  pixel.b = c[2];
}

void Renderer::renderLine(int x, Pixel** pixelGrid) {
  for (int j=0; j<SCREEN_HEIGHT; j++) {
    Pixel& pixel = pixelGrid[x][j];
    renderPixel(x, j, pixel);
    pixel.r = pixel.r > 255.f ? 255.f : pixel.r < 0.f ? 0.f : pixel.r;
    pixel.g = pixel.g > 255.f ? 255.f : pixel.g < 0.f ? 0.f : pixel.g;
    pixel.b = pixel.b > 255.f ? 255.f : pixel.b < 0.f ? 0.f : pixel.b;
  }
}
