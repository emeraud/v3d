#include "AnimationManager.hpp"

#include "SDL/SDL.h"

#include <iostream>
#include <climits>
#include <math.h>

#include "Viewer.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

#define PI 3.14159f

AnimationManager::AnimationManager(Viewer* viewer) : _viewer(viewer), _onMove(true), _onExit(false) {
  Vec3Df pos(3.f,3.f,2.f);
  Vec3Df dir = -1.f * pos;
  Vec3Df up(0.f, 0.f, 1.f);
  Vec3Df right(1.f, 0.f, 0.f);
  _camera = new Camera(pos, dir, up, right);
  _renderer = new Renderer(&_scene, _camera);
  _nbFrames = UINT_MAX;
  _t = 0.f;
  _invFrames = 0.f;
}


AnimationManager::~AnimationManager() {
  delete _renderer;
  delete _camera;
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
  if (nbFrames > 0) {
    _invFrames = 1.f / ((float) nbFrames);
  }
}

void AnimationManager::move() {
  _t += _invFrames;
  _camera->setPos(Vec3Df(5.f * cos(_t * 2.f * PI), 5.f * sin(_t * 2.f * PI), 3.f));
  _camera->setDir(-1.f * _camera->getPos());
  _camera->setUp(Vec3Df(0.f, 0.f, 1.f));
  _camera->setRight(Vec3Df::crossProduct(_camera->getDir(), _camera->getUp()));
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
