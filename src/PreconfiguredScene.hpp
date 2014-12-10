#ifndef PRECONFIGUREDSCENE_HPP
#define PRECONFIGUREDSCENE_HPP


#include "Viewer.hpp"
#include "AnimationManager.hpp"
#include "Connector3D.hpp"
#include "Object3D.hpp"
#include "Light.hpp"
#include "Vec3D.h"


class PreconfiguredScene {
  public:
    PreconfiguredScene();
    virtual ~PreconfiguredScene() { }

  public:
    void play();
 
  protected:
    virtual void _configure() = 0;
    void _play();
    void _playWithBench();

  protected:
    Viewer              _viewer;
    AnimationManager    _animationManager;
    bool                _activateBench;
};

class Scene_Ram_5Frames : public PreconfiguredScene {
  protected:
    virtual void _configure();
};

class Scene_Bunny_3Frames : public PreconfiguredScene {
  protected:
    virtual void _configure();
};

class Scene_Bunny_10Frames : public PreconfiguredScene {
  protected:
    virtual void _configure();
};

class Scene_Bunny_40Frames : public PreconfiguredScene {
  protected:
    virtual void _configure();
};

class Scene_Monkey_4Frames : public PreconfiguredScene {
  protected:
    virtual void _configure();
};

class Scene_MonkeyAndBunny_40Frames : public PreconfiguredScene {
  protected:
    virtual void _configure();
};

#endif

