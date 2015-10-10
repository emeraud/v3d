#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "SDL.h"

#include "Types.hpp"
#include "renderer/RenderingPipeline.hpp"

class Viewer;
class Model;

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
    Viewer*            _viewer;
    Model*             _model;
    RenderingPipeline  _renderingPipeline;

  private:
    bool          _onMove;
    bool          _onExit;
    UInt          _nbFrames;
    UInt          _currentFrame;
};

#endif
