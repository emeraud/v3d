#ifndef SCENE3D_HPP
#define SCENE3D_HPP

#include <vector>

class Object3D;

class Scene3D {
  public:
    Scene3D();
    ~Scene3D();


  private:
    std::vector<Object3D*>      _objects;

};

#endif
