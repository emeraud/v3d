#include "Object3D.hpp"

#include <iostream>
#include <cfloat>

Object3D::Object3D(Tessellation3D* tessellation) : _tessellation(tessellation) {
  _tessellation->computeVerticesNormals();
  _kdTree = new KDTree(_tessellation);
}

Object3D::~Object3D() {
  delete _kdTree;
  delete _tessellation;
}

Material Object3D::getMaterial() const {
  return _material;
}

void Object3D::setMaterial(const Material& material) {
  _material = material;
}

bool Object3D::intersect(const Ray& ray, Vec3Df& intersectionPoint, Vec3Df& intersectionNormal) const {
  std::vector<IntersectedNode> nodes;
  if (!_kdTree->getSortedIntersectedLeaves(ray, nodes)) {
    return false;
  }

  // loop
  float t,u,v;
  TriangleVertices intersectedTriangle;

  // best so far
  TriangleVertices bestTriangle;
  float uI = 0.f, vI = 0.f;
  float minDist = FLT_MAX;
  float sqMinDist = FLT_MAX;

  for (std::vector<IntersectedNode>::const_iterator nIt = nodes.begin(); nIt != nodes.end(); ++nIt) {
    if (nIt->sqDist > sqMinDist) {
      // all points of the box are worst than the intersected point
      // since the IntersectedNode list is sorted, we can stop
      break;
    }

    const std::vector<UInt>& triangles = nIt->node->getTriangles();
    for (UInt i=0; i<triangles.size(); i++) {
      intersectedTriangle = _tessellation->getTriangleVertices(triangles[i]);
      if (ray.intersect(intersectedTriangle.v0->pos, intersectedTriangle.v1->pos, intersectedTriangle.v2->pos, t, u, v)) {
        if (t < minDist) {
          minDist = t;
          sqMinDist = minDist * minDist;
          bestTriangle = intersectedTriangle;
          uI = u;
          vI = v;
        }
      }
    }
  }

  if (minDist != FLT_MAX) {
    intersectionPoint = ray.getOrigin() + minDist * ray.getDirection();
    intersectionNormal = (1.f - uI -vI) * bestTriangle.v0->normal + uI * bestTriangle.v1->normal + vI * bestTriangle.v2->normal;
    intersectionNormal.normalize();
    return true;
  }

  return false;
}

