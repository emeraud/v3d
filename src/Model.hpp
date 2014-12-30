#ifndef Model_HPP
#define Model_HPP

#include "Types.hpp"

class Scene3D;
class Camera;

class Model {
  public:
    Model();
    virtual ~Model();

  public:
    Scene3D* getScene();
    Camera* getCamera();
    bool isBenchActivated();
    UInt getNbFrames();

  public:
    void updateToFrame(UInt frame);
 
  protected:
    virtual void _configure() = 0;
    virtual void _move(float t);

  protected:
    Scene3D*            _scene;
    Camera*             _camera;

    UInt                _nbFrames;
    bool                _activateBench;
};

#endif

