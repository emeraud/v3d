#ifndef TESSELLATION_HPP
#define TESSELLATION_HPP

#include <vector>

#include "Types.hpp"
#include "Triangle.h"
#include "Vec3D.h"

struct Vertex {
  Vec3Df                      pos;
  Vec3Df                      normal;
  std::vector<UInt>   triangles;
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
    void resize(UInt nbVertices, UInt nbTriangles);
    const Vertex* getVertex(UInt idx) const;
    const Triangle* getTriangle(UInt idx) const;
    TriangleVertices getTriangleVertices(UInt idx) const;
    void setVertex(UInt idx, float x, float y, float z);
    void setTriangle(UInt idx, UInt v0, UInt v1, UInt v2);
    void applyTranslation(const Vec3Df &translation);
    void computeVerticesNormals();

    std::vector<const Vertex*> getVerticesView(); 
    std::vector<UInt> getTrianglesView(); 

  private:
    std::vector<Triangle*>       _triangles;
    std::vector<Vertex*>         _vertices;
};

#endif
