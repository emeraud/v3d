#include "AnimationManager.hpp"

#include "SDL/SDL.h"

#include <iostream>
#include <vector>

#include "Viewer.hpp"
#include "Connector3D.hpp" // FIXME temp
#include "Tessellation3D.hpp"
#include "KDTree.hpp"
#include "Light.hpp"
#include "BRDF.hpp"


AnimationManager::AnimationManager(Viewer* viewer) : _viewer(viewer), _onMove(true), _onExit(false) {
  _pixelGrid = new Pixel*[SCREEN_WIDTH];
  for (int i=0; i<SCREEN_WIDTH; i++) {
    _pixelGrid[i] = new Pixel[SCREEN_HEIGHT];
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      _pixelGrid[i][j].r = 0;
      _pixelGrid[i][j].g = 0;
      _pixelGrid[i][j].b = 0;
    }
  }

  _scene.addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene.addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/bunny.off")));
}


AnimationManager::~AnimationManager() {
  for (int i=0; i<SCREEN_WIDTH; i++) {
    delete[] _pixelGrid[i];
  }
  delete[] _pixelGrid;
}

void AnimationManager::run() {
  _viewer->update(getNextImage());
  while (true) {
    if (_onExit) {
      break;
    } else {
      waitEvents();
    }
  }

/*
  while (true) {
    if (_onExit) {
      break;
    } else if (_onMove) {
      _viewer->update(getNextImage());
      treatEvents();
    } else {
      waitEvents();
    }
  }
*/
}

Pixel** AnimationManager::getNextImage() {
  // TODO add configurable observator position & light
  const Object3D* object = _scene.getObjects()[0];
  Vec3Df obsPos(-2.f, 0.f, 0.f);
  Vec3Df obsDir(1.0f, 0.f, 0.f);
  Vec3Df obsRight(0.f, 1.f, 0.f);
  Vec3Df obsUp(0.f, 0.f, 1.f);

  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      // TODO FIXME: should be optimized (!) and configurable
      Vec3Df stepX = (float(i) - 0.5f * float(SCREEN_WIDTH))/float(SCREEN_WIDTH) * obsRight;
      Vec3Df stepY = (float(j) - 0.5f * float(SCREEN_HEIGHT))/float(SCREEN_HEIGHT) * obsUp;
      Ray ray(obsPos, obsDir + stepX + stepY);

      Vec3Df intersectionPoint;
      Vec3Df intersectionNormal;
      Vec3Df c(0.f, 0.f, 0.f);
      if (object->intersect(ray, intersectionPoint, intersectionNormal)) {
        BRDF::getColor(obsPos, intersectionPoint, intersectionNormal, object->getMaterial(), _scene.getLights(), c);
      }
      
      _pixelGrid[i][j].r = c[0];
      _pixelGrid[i][j].g = c[1];
      _pixelGrid[i][j].b = c[2];
    }
  }
  return _pixelGrid;
}

void AnimationManager::waitEvents() {
  SDL_Event event;
  SDL_WaitEvent(&event);
  handleEvent(event);
}

void AnimationManager::treatEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    handleEvent(event);
  }
}

void AnimationManager::handleEvent(const SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      handleKeyDownEvent(event.key.keysym.sym);
      break;

    case SDL_QUIT:
      _onExit = true;
      break;
  }
}

void AnimationManager::handleKeyDownEvent(int key) {
  switch(key){
    case SDLK_c:
      _onMove = !_onMove;
      break;
    case SDLK_ESCAPE:
      _onExit = true;
      break;
    default:
      break;
  }
}
