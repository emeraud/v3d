#include <iostream>

#include <SDL/SDL.h>

#include "Viewer.hpp"
#include "AnimationManager.hpp"

int main(int argc, char *argv[])
{
  // print args
  for (int i=0; i<argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  // let's move it on
  Viewer viewer;
  AnimationManager animationManager(&viewer);
  animationManager.run();

  return EXIT_SUCCESS;
}
