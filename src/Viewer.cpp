#include "Viewer.h"

#include <SDL/SDL.h>

Viewer::Viewer() {
  
  // sdl initialization
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("SDL Init", NULL);
  _screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);

  // pixels allocation
  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      _pixels[i][j] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
    }
  }
}

Viewer::~Viewer() {
  // release pixels
  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      SDL_FreeSurface(_pixels[i][j]);
    }
  }

  // release screen
  SDL_FreeSurface(_screen); 

  // quit sdl
  SDL_Quit();
}

void Viewer::update(Pixel** pixelGrid) {
  // display pixels array
  SDL_Rect pos;
  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      pos.x = i;
      pos.y = j;
      SDL_FillRect(_pixels[i][j], NULL, SDL_MapRGB(_screen->format, pixelGrid[i][j].r, pixelGrid[i][j].g, pixelGrid[i][j].b)); 
      SDL_BlitSurface(_pixels[i][j], NULL, _screen, &pos);
    }
  }

  SDL_Flip(_screen);
}
