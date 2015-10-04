#ifndef PIXEL_BLOCK_HPP
#define PIXEL_BLOCK_HPP

class PixelBlock {
public:
  PixelBlock();
  ~PixelBlock();

public:
  void init(int xMin, int xMax, int yMin, int yMax);

public:
  bool getNext(int& x, int& y);

private:
  int _xMin;
  int _xMax;
  int _yMin;
  int _yMax;

private:
  int _x;
  int _y;

public:
  // for debug
  int _threadId;
};

#endif

