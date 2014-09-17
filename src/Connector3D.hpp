#ifndef CONNECTOR3D_HPP
#define CONNECTOR3D_HPP

#include <string>

class Tessellation3D;

class Connector3D {
  public:
    Connector3D();
    ~Connector3D();

  public:
    Tessellation3D* parseFile(const std::string& fileName);
};

#endif
