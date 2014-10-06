#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "SDL/SDL.h"

#include "Types.hpp"
#include "Scene3D.hpp"
#include "Renderer.hpp"

class Viewer;

class AnimationManager {
  public:
    AnimationManager(Viewer* viewer);
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
    Camera        _camera;
    Renderer*     _renderer;
    Scene3D       _scene;
    bool          _onMove;
    bool          _onExit;
};

#endif
