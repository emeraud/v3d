#ifndef TESSELLATION_HPP
#define TESSELLATION_HPP

#include <vector>

#include "Triangle.h"
#include "Vec3D.h"

struct Vertex {
  Vec3Df                    pos;
  std::vector<Triangle*>    triangles;
};

class Tessellation3D {
  public:
    Tessellation3D();
    ~Tessellation3D();

  public:
    void resize(unsigned int nbVertices, unsigned int nbTriangles);
    const Vertex* getVertex(unsigned int idx) const;
    void setVertex(unsigned int idx, float x, float y, float z);
    void setTriangle(unsigned int idx, unsigned int v0, unsigned int v1, unsigned int v2);

    std::vector<const Vertex*> getVerticesView(); 

  private:
    std::vector<Triangle>        _triangles;
    std::vector<Vertex*>         _vertices;
};

#endif
