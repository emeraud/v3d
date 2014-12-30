#include "ModelObjectsHelper.hpp"

#include "Tessellation3D.hpp"
#include "Connector3D.hpp"


Tessellation3D* ModelObjectsHelper::buildTessellation(std::string path) {
  return Connector3D::parseFile(path.c_str());
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

