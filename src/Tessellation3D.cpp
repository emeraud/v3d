#include "Tessellation3D.hpp"

#include <iostream>

Tessellation3D::Tessellation3D() {

}

Tessellation3D::~Tessellation3D() {
  std::cout << "Dtor, nb vertices=" << _vertices.size() << " nbTriangles=" << _triangles.size() << std::endl;
}

void Tessellation3D::addVertex(float x, float y, float z) {
  _vertices.push_back(Vec3Df(x, y, z));
}

void Tessellation3D::addTriangle(unsigned int v0, unsigned int v1, unsigned int v2) {
  _triangles.push_back(Triangle(v0, v1, v2));
}
