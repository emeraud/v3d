#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Types.h"
#include "SDL/SDL.h"

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
    int           _state;
    bool          _onMove;
    bool          _onExit;
};

#endif
