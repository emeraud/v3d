#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

#include "Mesh3D.hpp"

class Object3D {
  public:
    Object3D();
    ~Object3D();

  private:
    Mesh3D mesh;
};

#endif
