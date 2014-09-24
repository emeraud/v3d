#ifndef CONNECTOR3D_HPP
#define CONNECTOR3D_HPP

#include <string>

class Tessellation3D;

class Connector3D {
  public:
    static Tessellation3D* parseFile(const std::string& fileName);

  private:
    Connector3D();
};

#endif
