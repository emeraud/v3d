#include "ModelObjectsHelper.hpp"

#include "Tessellation3D.hpp"
#include "Connector3D.hpp"


Tessellation3D* ModelObjectsHelper::buildTessellation(std::string path) {
  Tessellation3D* tessellation = Connector3D::parseFile(path.c_str());
  if (tessellation == 0x0) {
	  std::cout << "A problem occurred when reading file: " << path << std::endl;
	  std::cout << "Interrupting program" << std::endl;
	  exit(0);
	  return 0x0;
  }
  return tessellation;
}

Tessellation3D* ModelObjectsHelper::getRam() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/ram.off");
}

Tessellation3D* ModelObjectsHelper::getBunny() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/bunny.off");
}

Tessellation3D* ModelObjectsHelper::getMonkey() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/monkey.off");
}

Tessellation3D* ModelObjectsHelper::getRhino() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/rhino.off");
}

Tessellation3D* ModelObjectsHelper::getGargoyle() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/gargoyle.off");
}

Tessellation3D* ModelObjectsHelper::getGround() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/ground.off");
}

Tessellation3D* ModelObjectsHelper::getTeapot() {
  return buildTessellation("e:\\dev\\v3d\\models\\ram.off");
}

