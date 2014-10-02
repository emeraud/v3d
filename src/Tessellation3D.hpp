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

struct TriangleVertices {
  const Vertex* v0;
  const Vertex* v1;
  const Vertex* v2;

  TriangleVertices() : v0(0x0), v1(0x0), v2(0x0) { }
  TriangleVertices(const Vertex* iV0, const Vertex* iV1, const Vertex* iV2) : v0(iV0), v1(iV1), v2(iV2) { }
};

class Tessellation3D {
  public:
    Tessellation3D();
    ~Tessellation3D();

  public:
    void resize(unsigned int nbVertices, unsigned int nbTriangles);
    const Vertex* getVertex(unsigned int idx) const;
    const Triangle* getTriangle(unsigned int idx) const;
    TriangleVertices getTriangleVertices(unsigned int idx) const;
    TriangleVertices getTriangleVertices(const Triangle*) const; // TODO FIXME trash, only use indexes
    void setVertex(unsigned int idx, float x, float y, float z);
    void setTriangle(unsigned int idx, unsigned int v0, unsigned int v1, unsigned int v2);
    void computeVerticesNormals();

    std::vector<const Vertex*> getVerticesView(); 
    std::vector<const Triangle*> getTrianglesView(); 

  private:
    std::vector<Triangle*>       _triangles;
    std::vector<Vertex*>         _vertices;
};

#endif
