#ifndef CONFIG_HPP
#define CONFIG_HPP

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define NB_THREADS 16
#define ENABLE_SHADOW 1
#define DISPLAY_LIGHTS_SOURCES 1


#include "../external/pugixml/pugixml.hpp"


class Config {
public:
  Config();
  ~Config();

public:
  int width;
  int height;

  bool withShadow;
  bool withLightSource;

  int nbThreads;
};

#endif
