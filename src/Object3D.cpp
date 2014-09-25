#include "Object3D.hpp"

#include <iostream>
#include <cfloat>

Object3D::Object3D(Tessellation3D* tessellation) : _tessellation(tessellation) {
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
  std::vector<IntersectedNode> nodes = _kdTree->getSortedIntersectedLeaves(ray);
  float t,u,v;
  const Vertex *v0, *v1, *v2;

  // best so far
  const Vertex *i0, *i1, *i2;
  float minDist = FLT_MAX;
  float sqMinDist = FLT_MAX;

  for (std::vector<IntersectedNode>::const_iterator nIt = nodes.begin(); nIt != nodes.end(); ++nIt) {
    if (nIt->sqDist > sqMinDist) {
      // all points of the box are worst than the intersected point
      // since the IntersectedNode list is sorted, we can stop
      break;
    }

    std::vector<const Vertex*> vertices = nIt->node->getVertices();
    for (std::vector<const Vertex*>::const_iterator vIt = vertices.begin(); vIt != vertices.end(); ++vIt) {
      for (std::vector<unsigned int>::const_iterator tIt = (*vIt)->triangles.begin(); tIt != (*vIt)->triangles.end(); ++tIt) {
        Triangle triangle = _tessellation->getTriangle(*tIt);
        v0 = _tessellation->getVertex(triangle.getVertex(0));
        v1 = _tessellation->getVertex(triangle.getVertex(1));
        v2 = _tessellation->getVertex(triangle.getVertex(2));
        if (ray.intersect(v0->pos, v1->pos, v2->pos, t, u, v)) {
          if (t < minDist) {
            minDist = t;
            sqMinDist = minDist * minDist;
            i0 = v0;
            i1 = v1;
            i2 = v2;
          }
        }
      }
    }
  }

  if (minDist != FLT_MAX) {
    intersectionPoint = ray.getOrigin() + minDist * ray.getDirection();
    intersectionNormal = Vec3Df::crossProduct(i2->pos-i0->pos, i1->pos-i0->pos);
    intersectionNormal.normalize();
    return true;
  }

  return false;
}
