#include "AnimationManager.hpp"

#include "SDL/SDL.h"

#include <iostream>

#include "Viewer.hpp"
#include "Connector3D.hpp" // FIXME temp
#include "Tessellation3D.hpp"


AnimationManager::AnimationManager(Viewer* viewer) : _viewer(viewer), _state(0), _onMove(true), _onExit(false) {
  _pixelGrid = new Pixel*[SCREEN_WIDTH];
  for (int i=0; i<SCREEN_WIDTH; i++) {
    _pixelGrid[i] = new Pixel[SCREEN_HEIGHT];
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      _pixelGrid[i][j].r = 0;
      _pixelGrid[i][j].g = 0;
      _pixelGrid[i][j].b = 0;
    }
  }

  // TEMP, TODO FIXME
  Connector3D connector;
  Tessellation3D* tessellation;
  tessellation = connector.parseFile("/home/val/Documents/dev/3d/raytracer/models/bunny.off");
  delete tessellation;
  tessellation = connector.parseFile("/home/val/Documents/dev/3d/raytracer/models/fandisk.off");
  delete tessellation;
}


AnimationManager::~AnimationManager() {
  for (int i=0; i<SCREEN_WIDTH; i++) {
    delete[] _pixelGrid[i];
  }
  delete[] _pixelGrid;
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

Pixel** AnimationManager::getNextImage() {
  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      _pixelGrid[i][j].r = i%256;
      _pixelGrid[i][j].g = j%256;
      _pixelGrid[i][j].b = (i+j+_state)%256;
    }
  }
  _state++;
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
