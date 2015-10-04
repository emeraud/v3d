#include "PixelBlock.hpp"

#include <iostream>

PixelBlock::PixelBlock() {

}

PixelBlock::~PixelBlock() {

}

void PixelBlock::init(int xMin, int xMax, int yMin, int yMax) {
  // std::cout << "init block for thread " << _threadId << " "
  //           << "x=[" << xMin << "," << xMax << "] "
  //           << "y=[" << yMin << "," << yMax << "] "
  //           << std::endl;
            
  _xMin = xMin;
  _xMax = xMax;
  _yMin = yMin;
  _yMax = yMax;

  _x = _xMin;
  _y = _yMin;
}

bool PixelBlock::getNext(int& x, int &y) {
  if (_y > _yMax) {
    return false;
  }

  x = _x;
  y = _y;

  //std::cout << "\tnext=" << x << "," << y << std::endl;

  if (_x == _xMax) {
    _x = _xMin;
    _y++;
  } else {
    _x++;
  }

  return true;
}

