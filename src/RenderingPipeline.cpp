#include "RenderingPipeline.hpp"

#include <thread>

#include "Types.hpp"
#include "Model.hpp"
#include "Renderer.hpp"
#include "Dispatcher.hpp"

RenderingPipeline::RenderingPipeline(Model* model) : _model(model) {
#ifdef NB_THREADS
  _renderer = new Renderer*[NB_THREADS];
  for (int i=0; i<NB_THREADS; i++) {
    _renderer[i] = new Renderer(_model->getScene(), _model->getCamera());
    _renderer[i]->_threadId = i;
  }
#else
  _renderer = new Renderer(_model->getScene(), _model->getCamera());
#endif

  _pixelGrid = new Pixel*[SCREEN_WIDTH];
  for (int i=0; i<SCREEN_WIDTH; i++) {
    _pixelGrid[i] = new Pixel[SCREEN_HEIGHT];
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      _pixelGrid[i][j].r = 0;
      _pixelGrid[i][j].g = 0;
      _pixelGrid[i][j].b = 0;
    }
  }
}

RenderingPipeline::~RenderingPipeline() {
#ifdef NB_THREADS
  for (int i=0; i<NB_THREADS; i++) {
    delete _renderer[i];
  }
#else
  delete _renderer;
#endif

  for (int i=0; i<SCREEN_WIDTH; i++) {
    delete[] _pixelGrid[i];
  }
  delete[] _pixelGrid;
}

Pixel** RenderingPipeline::render() {
#ifdef NB_THREADS
  std::thread threads[NB_THREADS];
  Dispatcher dispatcher(_pixelGrid, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
  for (int i=0; i<NB_THREADS; i++) {
    threads[i] = std::thread(&Renderer::render, _renderer[i], &dispatcher, _pixelGrid);
  }

  for (int i=0; i<NB_THREADS; i++) {
    threads[i].join();
  }
#else
  for (int i=0; i<SCREEN_WIDTH; i++) {
    for (int j=0; j<SCREEN_HEIGHT; j++) {
      Pixel& pixel = _pixelGrid[i][j];
      _renderer->renderPixel(i, j, pixel);
    }
  }
#endif
  return _pixelGrid;
}

