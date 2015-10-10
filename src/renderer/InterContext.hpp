#ifndef INTERCONTEXT_HPP
#define INTERCONTEXT_HPP

#include "geo/Ray.hpp"
#include "geo/Vec3D.h"
#include "geo/KDTree.hpp" // IntersectedNode, remove this dep if possible

class Object3D;

struct InterContext {
  Ray ray; 
  Vec3Df point;
  Vec3Df normal;
  Object3D* object;

  Vec3Df tmpPoint;
  Vec3Df tmpNormal;

  UInt nbNodes;
  std::vector<IntersectedNode> nodes;
};

#endif

