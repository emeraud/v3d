#include "AnimationManager.hpp"

#include "SDL/SDL.h"

#include <iostream>
#include <climits>

#include "Viewer.hpp"


AnimationManager::AnimationManager(Viewer* viewer) : _viewer(viewer), _onMove(true), _onExit(false) {
  _camera = Camera(Vec3Df(3.f, -3.f, 0.f));
  _renderer = new Renderer(&_scene, &_camera);
  _nbFrames = UINT_MAX;
}


AnimationManager::~AnimationManager() {
  delete _renderer;
}

void AnimationManager::run() {
  std::cout << "Running animation with " << _nbFrames << " frames" << std::endl;
#ifdef NB_THREADS
  std::cout << "Multithreaded rendering with " << NB_THREADS << " threads" << std::endl;
#else
  std::cout << "Monothreaded rendering" << std::endl;
#endif
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

Scene3D& AnimationManager::getScene() {
  return _scene;
}
void AnimationManager::setNbFrames(UInt nbFrames) {
  _nbFrames = nbFrames;
}

void AnimationManager::move() {
  Vec3Df rotationAxis = Vec3Df(0.f, 1.f, 0.f);
  Vec3Df movement = Vec3Df::crossProduct(_camera.pos, rotationAxis);
  movement.normalize();
  movement = 0.2f * movement;
  _camera.updatePos(_camera.pos + movement);
  _nbFrames--;
  if (_nbFrames == 0) {
    _onExit = true;
  }
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
