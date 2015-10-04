#include "AnimationManager.hpp"

#include <iostream>
#include <climits>
#include <math.h>

#include "Viewer.hpp"
#include "Model.hpp"

AnimationManager::AnimationManager(Model* model) : _model(model), _renderingPipeline(model), _onMove(true), _onExit(false) {
  _viewer = new Viewer();
  _nbFrames = _model->getNbFrames();
  _currentFrame = 0;
}


AnimationManager::~AnimationManager() {
  delete _viewer;
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

void AnimationManager::move() {
  _model->updateToFrame(_currentFrame);
  _currentFrame++;
  if (_currentFrame > _nbFrames) {
    _onExit = true;
  }
}

Pixel** AnimationManager::getNextImage() {
  move();
  return _renderingPipeline.render();
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
