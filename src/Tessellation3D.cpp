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
  _triangleNormals.resize(nbTriangles);
  std::cout << "Resize, nb vertices=" << _vertices.size() << " nbTriangles=" << _triangles.size() << std::endl;
}

const Vertex* Tessellation3D::getVertex(unsigned int idx) const {
  return _vertices[idx];
}

const Triangle& Tessellation3D::getTriangle(unsigned int idx) const {
  return _triangles[idx];
}

void Tessellation3D::setVertex(unsigned int idx, float x, float y, float z) {
  _vertices[idx] = new Vertex();
  _vertices[idx]->pos = Vec3Df(x, y, z);
  _vertices[idx]->normal = Vec3Df(0.f, 0.f, 0.f);
}

void Tessellation3D::setTriangle(unsigned int idx, unsigned int v0, unsigned int v1, unsigned int v2) {
  _triangles[idx] = Triangle(v0, v1, v2);
  _vertices[v0]->triangles.push_back(idx);
  _vertices[v1]->triangles.push_back(idx);
  _vertices[v2]->triangles.push_back(idx);
}

std::vector<const Vertex*> Tessellation3D::getVerticesView() {
  std::vector<const Vertex*> verticesView;
  verticesView.resize(_vertices.size());

  for (unsigned int i=0; i<_vertices.size(); ++i) {
    verticesView[i] = _vertices[i];
  }

  return verticesView;
}

void Tessellation3D::computeVerticesNormals() {
  std::vector<Vec3Df> triangleNormals;
  std::vector<float> triangleAreas;

  triangleNormals.resize(_triangles.size());
  triangleAreas.resize(_triangles.size());

  unsigned int v0, v1, v2;
  Vec3Df e0;
  Vec3Df e1;

  for (unsigned int idx=0; idx<_triangles.size(); idx++) {
    v0 = _triangles[idx].getVertex(0);
    v1 = _triangles[idx].getVertex(1);
    v2 = _triangles[idx].getVertex(2);

    e0 = _vertices[v1]->pos - _vertices[v0]->pos;
    e1 = _vertices[v2]->pos - _vertices[v0]->pos;
    
    triangleNormals[idx] = Vec3Df::crossProduct(e0, e1);
    triangleAreas[idx] = 0.5f * triangleNormals[idx].getLength();
    triangleNormals[idx].normalize();
  }

  Vertex* vertex;
  for (unsigned int i=0; i<_vertices.size(); i++) {
    vertex = _vertices[i];
    for (unsigned int j=0; j<_triangles.size(); j++) {
      vertex->normal = vertex->normal + triangleAreas[vertex->triangles[j]] * triangleNormals[vertex->triangles[j]];
    }
    vertex->normal.normalize();
  }
}

