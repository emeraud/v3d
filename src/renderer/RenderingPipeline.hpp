#ifndef RENDERING_PIPELINE_HPP
#define RENDERING_PIPELINE_HPP

#include "config/Config.hpp"

class Model;
class Renderer;
class Pixel;

class RenderingPipeline {
public:
  RenderingPipeline(Model* model);
  ~RenderingPipeline();

public:
  Pixel** render();

private:
  Pixel**   _pixelGrid;

private:
  Model*    _model;

#ifdef NB_THREADS
  Renderer** _renderer;
#else
  Renderer* _renderer;
#endif

};

#endif

