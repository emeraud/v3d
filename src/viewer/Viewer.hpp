#ifndef VIEWER_HPP
#define VIEWER_HPP

#include "config/Config.hpp"
#include "Types.hpp"

struct SDL_Surface;

class Viewer {
public:
  Viewer();
  ~Viewer();

public:
  void update(Pixel** pixelGrid);

private:
  SDL_Surface *   _pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
  SDL_Surface *   _screen; // freed by SQL_QUIT
};

#endif
