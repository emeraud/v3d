#include "RenderingPipeline.hpp"

#include <thread>

#include "Types.hpp"
#include "Model.hpp"
#include "Renderer.hpp"

RenderingPipeline::RenderingPipeline(Model* model) : _model(model) {
#ifdef NB_THREADS
  _renderer = new Renderer*[NB_THREADS];
  for (int i=0; i<NB_THREADS; i++) {
    _renderer[i] = new Renderer(_model->getScene(), _model->getCamera());
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
  int currentLine = 0;
  int maxThreadId = 0;

  while (currentLine < SCREEN_WIDTH) {
    maxThreadId = 0;
    for (int i=0; i<NB_THREADS; i++) {
      if (currentLine >= SCREEN_WIDTH) break;
      //std::cout << "currentLine " << currentLine << " for thread=" << i << std::endl;
      threads[i] = std::thread(&Renderer::renderLine, _renderer[i], currentLine, _pixelGrid);
      maxThreadId++; 
      currentLine++;
    }

    for (int i=0; i<maxThreadId; i++) {
      threads[i].join();
    }
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

