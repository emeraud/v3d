#include "AnimationManager.hpp"

#include "SDL/SDL.h"

#include <iostream>
#include <vector>
#include <thread>

#include "Viewer.hpp"
#include "Connector3D.hpp" // FIXME temp
#include "KDTree.hpp"
#include "Light.hpp"
#include "BRDF.hpp"


AnimationManager::AnimationManager(Viewer* viewer) : _viewer(viewer), _onMove(true), _onExit(false) {
  _scene.addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  //_scene.addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/ram.off")));
  _scene.addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/bunny.off")));
  //_scene.addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/monkey.off")));
  //_scene.addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/Ramesses.off")));

  _camera = Camera(Vec3Df(3.f, -3.f, 0.f));
  _renderer = new Renderer(&_scene, &_camera);
}


AnimationManager::~AnimationManager() {
  delete _renderer;
}

void AnimationManager::run() {
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
}

void AnimationManager::move() {
  Vec3Df rotationAxis = Vec3Df(0.f, 1.f, 0.f);
  Vec3Df movement = Vec3Df::crossProduct(_camera.pos, rotationAxis);
  movement.normalize();
  movement = 0.2f * movement;
  _camera.updatePos(_camera.pos + movement);
}

Pixel** AnimationManager::getNextImage() {
  move();
  return _renderer->render();
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
