#include "Dispatcher.hpp"

#include "Types.hpp"

Dispatcher::Dispatcher(Pixel** pixelGrid, int xMax, int yMax)
  : _xMax(xMax), _yMax(yMax) {
  _x = 0;
  _y = 0;
  _step = 25;
}

Dispatcher::~Dispatcher() {

}

bool Dispatcher::getNextBlock(PixelBlock& pixelBlock) {
  mutex.lock();
  if (_y > _yMax) {
    mutex.unlock();
    return false;
  }

  int xMax = std::min(_x + _step, _xMax);
  int yMax = std::min(_y + _step, _yMax);

  pixelBlock.init(_x, xMax, _y, yMax);

  if (xMax >= _xMax) {
    _x = 0;
    _y += _step;
  } else {
    _x = xMax;
  }
  
  mutex.unlock();
  return true;

}

