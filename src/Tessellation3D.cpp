#include "Tessellation3D.hpp"

#include <iostream>

Tessellation3D::Tessellation3D() {

}

Tessellation3D::~Tessellation3D() {
  std::cout << "Dtor, nb vertices=" << _vertices.size() << " nbTriangles=" << _triangles.size() << std::endl;
  for (unsigned int i=0; i<_vertices.size(); i++) {
    delete _vertices[i];
  }
}

void Tessellation3D::resize(unsigned int nbVertices, unsigned int nbTriangles) {
  _vertices.resize(nbVertices, 0x0); 
  _triangles.resize(nbTriangles);
  std::cout << "Resize, nb vertices=" << _vertices.size() << " nbTriangles=" << _triangles.size() << std::endl;
}

const Vertex* Tessellation3D::getVertex(unsigned int idx) const {
  return _vertices[idx];
}

void Tessellation3D::setVertex(unsigned int idx, float x, float y, float z) {
  _vertices[idx] = new Vertex();
  _vertices[idx]->pos = Vec3Df(x, y, z);
}

void Tessellation3D::setTriangle(unsigned int idx, unsigned int v0, unsigned int v1, unsigned int v2) {
  _triangles[idx] = Triangle(v0, v1, v2);
  _vertices[v0]->triangles.push_back(&_triangles[idx]);
  _vertices[v1]->triangles.push_back(&_triangles[idx]);
  _vertices[v2]->triangles.push_back(&_triangles[idx]);
}

std::vector<const Vertex*> Tessellation3D::getVerticesView() {
  std::vector<const Vertex*> verticesView;
  verticesView.resize(_vertices.size());

  for (unsigned int i=0; i<_vertices.size(); ++i) {
    verticesView[i] = _vertices[i];
  }

  return verticesView;
}
