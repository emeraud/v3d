#ifndef SCENE3D_HPP
#define SCENE3D_HPP

#include <vector>

#include "Object3D.hpp"

class Scene3D {
  public:
    Scene3D();
    ~Scene3D();

  private:
    std::vector<Object3D> _objects;

};

#endif
