#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <mutex>

#include "PixelBlock.hpp"

class Pixel;

class Dispatcher {
public:
  Dispatcher(Pixel** pixelGrid, int xMax, int yMax);
  ~Dispatcher();

public:
  bool getNextBlock(PixelBlock& pixelBlock);

private:
  Pixel** _pixelGrid;
  int _xMax;
  int _yMax;

  int _x;
  int _y;
  int _step;

  std::mutex mutex;
};

#endif

