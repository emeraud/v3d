#ifndef VIEWER_H
#define VIEWER_H

#include "Config.h"
#include "Types.h"

class SDL_Surface;

class Viewer {
public:
  Viewer();
  ~Viewer();

public:
  void update(Pixel** pixelGrid);

private:
  SDL_Surface *   _pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
  SDL_Surface *   _screen;
};

#endif
