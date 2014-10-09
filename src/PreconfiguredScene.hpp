#ifndef PRECONFIGUREDSCENE_HPP
#define PRECONFIGUREDSCENE_HPP

class PreconfiguredScene {
  public:
    PreconfiguredScene() : _animationManager(&_viewer), _activateBench(false) {
      
    }
    virtual ~PreconfiguredScene() { }

  public:
    void play() {
      _configure();
      if (_activateBench) {
        _playWithBench();
      } else {
        _play();
      }
    }
 
  protected:
    virtual void _configure() = 0;
    void _play() {
      _animationManager.run();
    }
    void _playWithBench() {
      std::cout << "Now running" << std::endl;
      auto start = std::chrono::system_clock::now();
      _play();
      auto end = std::chrono::system_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      std::cout << elapsed.count() << " ms" << std::endl;
    }

  protected:
    Viewer              _viewer;
    AnimationManager    _animationManager;
    bool                _activateBench;
};

class Scene_Ram_5Frames : public PreconfiguredScene {
  public:
    Scene_Ram_5Frames () : PreconfiguredScene() {}
    virtual ~Scene_Ram_5Frames () { }

  protected:
    virtual void _configure() {
      _animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
      _animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/ram.off")));
      _animationManager.setNbFrames(5);
      _activateBench = true;
    }
};

class Scene_Bunny_3Frames : public PreconfiguredScene {
  public:
    Scene_Bunny_3Frames () : PreconfiguredScene() {}
    virtual ~Scene_Bunny_3Frames () { }

  protected:
    virtual void _configure() {
      _animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
      _animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/bunny.off")));
      _animationManager.setNbFrames(3);
      _activateBench = true;
    }
};

class Scene_Monkey_4Frames : public PreconfiguredScene {
  public:
    Scene_Monkey_4Frames () : PreconfiguredScene() {}
    virtual ~Scene_Monkey_4Frames () { }

  protected:
    virtual void _configure() {
      _animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
      _animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/monkey.off")));
      _animationManager.setNbFrames(4);
      _activateBench = true;
    }
};

#endif

