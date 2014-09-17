#include "Scene3D.hpp"

#include "Object3D.hpp"

Scene3D::Scene3D() {

}

Scene3D::~Scene3D() {
  for (unsigned int i=0; i<_objects.size(); i++) {
    delete _objects[i];
  }
  _objects.resize(0);
}

