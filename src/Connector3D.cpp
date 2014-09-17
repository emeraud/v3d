#include "Connector3D.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Tessellation3D.hpp"

Connector3D::Connector3D() {

}

Connector3D::~Connector3D() {

}

Tessellation3D* Connector3D::parseFile(const std::string& fileName) {
  std::ifstream file(fileName.c_str(), std::ios::binary);
  file.seekg(0, std::ios::end);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  // Read the hole file
  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size)) {
    return 0x0;
  }

  // Check size
  if (buffer.size() < 4) {
    return 0x0;
  }

  // Check header
  if (buffer[0] != 'O' || buffer[1] != 'F' || buffer[2] != 'F') {
    return 0x0;
  }

  // Zap comments and empty lines
  char* p = &buffer.front()+3;
  char* end = &buffer.back();
  while (p != end) {
    if (*p == ' ' || *p == '#') {
      for (; *p != '\n' || p != end; ++p);
    } else {
      break;
    }
  }

  // Check the end is not reached
  if (p == end) {
    return 0x0;
  }

  // Fill stream
  std::stringstream s;
  s << p;

  // Parse it
  Tessellation3D* tessellation = new Tessellation3D();

  int nbPoints, nbTriangles, nbLines;
  float x, y, z;
  unsigned int nbVertices;
  unsigned int v0, v1, v2;


  // first line, giving nb points, nb triangles, nb lines
  if (!((s >> nbPoints) && (s >> nbTriangles) && (s >> nbLines))) {
    goto error;
  }

  // vertices
  for (int i=0; i<nbPoints; i++) {
    if (!((s >> x) && (s >> y) && (s >> z))) {
      goto error;
    }
    tessellation->addVertex(x, y, z);
  }

  // triangles
  for (int i=0; i<nbTriangles; i++) {
    if (!((s >> nbVertices) && (nbVertices == 3) && (s >> v0) && (s >> v1) && (s >> v2))) {
      goto error;
    }
    tessellation->addTriangle(v0, v1, v2);
  }

  return tessellation;

  error:
    delete tessellation;
    return 0x0;
}
