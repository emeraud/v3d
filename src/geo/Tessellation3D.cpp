#include "Tessellation3D.hpp"

#include <iostream>

Tessellation3D::Tessellation3D() {

}

Tessellation3D::~Tessellation3D() {
  for (UInt i=0; i<_vertices.size(); i++) {
    delete _vertices[i];
  }
}

void Tessellation3D::resize(UInt nbVertices, UInt nbTriangles) {
  _vertices.resize(nbVertices, 0x0); 
  _triangles.resize(nbTriangles);
}

const Vertex* Tessellation3D::getVertex(UInt idx) const {
  return _vertices[idx];
}

const Triangle* Tessellation3D::getTriangle(UInt idx) const {
  return _triangles[idx];
}

TriangleVertices Tessellation3D::getTriangleVertices(UInt idx) const {
  Triangle* triangle = _triangles[idx];
  return TriangleVertices(_vertices[triangle->getVertex(0)],
                          _vertices[triangle->getVertex(1)],
                          _vertices[triangle->getVertex(2)]);
}

void Tessellation3D::setVertex(UInt idx, float x, float y, float z) {
  _vertices[idx] = new Vertex();
  _vertices[idx]->pos = Vec3Df(x, y, z);
  _vertices[idx]->normal = Vec3Df(0.f, 0.f, 0.f);
}

void Tessellation3D::setTriangle(UInt idx, UInt v0, UInt v1, UInt v2) {
  _triangles[idx] = new Triangle(v0, v1, v2);
  _vertices[v0]->triangles.push_back(idx);
  _vertices[v1]->triangles.push_back(idx);
  _vertices[v2]->triangles.push_back(idx);
}

std::vector<const Vertex*> Tessellation3D::getVerticesView() {
  std::vector<const Vertex*> verticesView;
  verticesView.resize(_vertices.size());

  for (UInt i=0; i<_vertices.size(); ++i) {
    verticesView[i] = _vertices[i];
  }

  return verticesView;
}

std::vector<UInt> Tessellation3D::getTrianglesView() {
  std::vector<UInt> trianglesView;
  trianglesView.resize(_triangles.size());

  for (UInt i=0; i<_triangles.size(); ++i) {
    trianglesView[i] = i;
  }

  return trianglesView;
}

void Tessellation3D::applyTranslation(const Vec3Df &translation) {
  for (UInt i=0; i<_vertices.size(); i++) {
    _vertices[i]->pos += translation;
  }
}

void Tessellation3D::computeVerticesNormals() {
  std::vector<Vec3Df> triangleNormals;
  std::vector<float> triangleAreas;

  triangleNormals.resize(_triangles.size());
  triangleAreas.resize(_triangles.size());

  UInt v0, v1, v2;
  Vec3Df e0;
  Vec3Df e1;

  for (UInt idx=0; idx<_triangles.size(); idx++) {
    v0 = _triangles[idx]->getVertex(0);
    v1 = _triangles[idx]->getVertex(1);
    v2 = _triangles[idx]->getVertex(2);

    e0 = _vertices[v1]->pos - _vertices[v0]->pos;
    e1 = _vertices[v2]->pos - _vertices[v0]->pos;
    
    triangleNormals[idx] = Vec3Df::crossProduct(e0, e1);
    triangleAreas[idx] = 0.5f * triangleNormals[idx].getLength();
    triangleNormals[idx].normalize();
  }

  Vertex* vertex;
  for (UInt i=0; i<_vertices.size(); i++) {
    vertex = _vertices[i];
    for (UInt j=0; j<vertex->triangles.size(); j++) {
      vertex->normal = vertex->normal + triangleAreas[vertex->triangles[j]] * triangleNormals[vertex->triangles[j]];
    }
    vertex->normal.normalize();
  }
}

