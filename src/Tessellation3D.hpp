#ifndef TESSELLATION_HPP
#define TESSELLATION_HPP

#include <vector>

#include "Triangle.h"
#include "Vec3D.h"

class Tessellation3D {
  public:
    Tessellation3D();
    ~Tessellation3D();
    void addVertex(float x, float y, float z);
    void addTriangle(unsigned int v0, unsigned int v1, unsigned int v2);

  private:
    std::vector<Triangle>     _triangles;
    std::vector<Vec3Df>       _vertices;
};

#endif
