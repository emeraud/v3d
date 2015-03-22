#include "Object3D.hpp"

#include <cfloat>

// Base object implem
Object3D::Object3D() {

}

Object3D::~Object3D() {

}

Material Object3D::getMaterial() const {
  return _material;
}

void Object3D::setMaterial(const Material& material) {
  _material = material;
}

// Triangular mesh implem
MeshObject3D::MeshObject3D(Tessellation3D* tessellation) : _tessellation(tessellation) {
  init();
}

MeshObject3D::MeshObject3D(Tessellation3D* tessellation, const Vec3Df &position) : _tessellation(tessellation) {
  _tessellation->applyTranslation(position);
  init();
}

MeshObject3D::~MeshObject3D() {
  delete _kdTree;
  delete _tessellation;
}

void MeshObject3D::init() {
  _tessellation->computeVerticesNormals();
  _kdTree = new KDTree(_tessellation);
}

bool MeshObject3D::intersect(InterContext& interContext) const {
  if (!_kdTree->getSortedIntersectedLeaves(interContext.ray, interContext.nodes, interContext.nbNodes)) {
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
  UInt nodeId = 0;

  for (std::vector<IntersectedNode>::const_iterator nIt = interContext.nodes.begin(); nodeId < interContext.nbNodes && nIt != interContext.nodes.end(); ++nIt) {
    if (nIt->sqDist > sqMinDist) {
      // all points of the box are worst than the intersected point
      // since the IntersectedNode list is sorted, we can stop
      break;
    }

    const std::vector<UInt>& triangles = nIt->node->getTriangles();
    for (UInt i=0; i<triangles.size(); i++) {
      intersectedTriangle = _tessellation->getTriangleVertices(triangles[i]);
      if (interContext.ray.intersect(intersectedTriangle.v0->pos, intersectedTriangle.v1->pos, intersectedTriangle.v2->pos, t, u, v)) {
        if (t < minDist) {
          minDist = t;
          sqMinDist = minDist * minDist;
          bestTriangle = intersectedTriangle;
          uI = u;
          vI = v;
        }
      }
    }
    nodeId++;
  }

  if (minDist != FLT_MAX) {
    interContext.tmpPoint = interContext.ray.getOrigin() + minDist * interContext.ray.getDirection();
    interContext.tmpNormal = (1.f - uI -vI) * bestTriangle.v0->normal + uI * bestTriangle.v1->normal + vI * bestTriangle.v2->normal;
    interContext.tmpNormal.normalize();
    return true;
  }

  return false;
}

// Sphere implem
SphereObject3D::SphereObject3D(Vec3Df center, float radius) : _center(center), _radius(radius) {

}

SphereObject3D::~SphereObject3D() {

}

bool SphereObject3D::intersect(InterContext& interContext) const {
  return interContext.ray.intersect(_center, _radius, interContext.tmpPoint, interContext.tmpNormal);
}

// Plan implem
PlanObject3D::PlanObject3D(Vec3Df point, Vec3Df normal) : _point(point), _normal(normal) {
  _normal.normalize();
}

PlanObject3D::~PlanObject3D() {

}

bool PlanObject3D::intersect(InterContext& interContext) const {
  float denominator = Vec3Df::dotProduct(_normal, interContext.ray.getDirection());
  if (denominator > -EPSILON && denominator < EPSILON) {
    // ray is parallel to plan
    return false;
  }

  float t = Vec3Df::dotProduct(_normal, _point - interContext.ray.getOrigin()) / denominator;

  if (t < 0.f) {
    // plan is behind ray
    return false;
  }

  interContext.tmpPoint = interContext.ray.getOrigin() + t * interContext.ray.getDirection();
  interContext.tmpNormal = _normal;

  return true;
}

