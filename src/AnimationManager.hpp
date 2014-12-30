#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "SDL/SDL.h"

#include "Types.hpp"

class Viewer;
class Model;
class Renderer;

class AnimationManager {
  public:
    AnimationManager(Model* model);
    ~AnimationManager();

  public:
    void run();

  private:
    void move();
    Pixel** getNextImage();

    void treatEvents();
    void waitEvents();

    void handleEvent(const SDL_Event& event);
    void handleKeyDownEvent(int key);

  private:
    Viewer*       _viewer;
    Model*        _model;
    Renderer*     _renderer;
    bool          _onMove;
    bool          _onExit;
    UInt          _nbFrames;
    UInt          _currentFrame;
};

#endif
