#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "SDL/SDL.h"

#include "Types.hpp"
#include "Scene3D.hpp"

class Viewer;

class AnimationManager {
  public:
    AnimationManager(Viewer* viewer);
    ~AnimationManager();

  public:
    void run();

  private:
    Pixel** getNextImage();

    void treatEvents();
    void waitEvents();

    void handleEvent(const SDL_Event& event);
    void handleKeyDownEvent(int key);

  private:
    Viewer*       _viewer;
    Pixel**       _pixelGrid;
    Scene3D       _scene;
    int           _state;
    bool          _onMove;
    bool          _onExit;
};

#endif
