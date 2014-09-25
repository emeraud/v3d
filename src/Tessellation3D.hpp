#ifndef TESSELLATION_HPP
#define TESSELLATION_HPP

#include <vector>

#include "Triangle.h"
#include "Vec3D.h"

struct Vertex {
  Vec3Df                      pos;
  Vec3Df                      normal;
  std::vector<unsigned int>   triangles;
};

class Tessellation3D {
  public:
    Tessellation3D();
    ~Tessellation3D();

  public:
    void resize(unsigned int nbVertices, unsigned int nbTriangles);
    const Vertex* getVertex(unsigned int idx) const;
    const Triangle& getTriangle(unsigned int idx) const;
    void setVertex(unsigned int idx, float x, float y, float z);
    void setTriangle(unsigned int idx, unsigned int v0, unsigned int v1, unsigned int v2);
    void computeVerticesNormals();

    std::vector<const Vertex*> getVerticesView(); 

  private:
    // TODO FIXME group Triangle and normals
    std::vector<Triangle>        _triangles;
    std::vector<Vec3Df>          _triangleNormals;
    std::vector<Vertex*>         _vertices;
};

#endif
