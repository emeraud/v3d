#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

#include "Tessellation3D.hpp"
#include "KDTree.hpp"
#include "Material.hpp"

class Object3D {
  public:
    Object3D(Tessellation3D* tessellation);
    ~Object3D();

  public:
    bool intersect(const Ray& ray, Vec3Df& intersectionPoint, Vec3Df& intersectionNormal) const;
    Material getMaterial() const;
    void setMaterial(const Material& material);

  private:
    Tessellation3D*   _tessellation;
    KDTree*           _kdTree;
    Material          _material;
};

#endif
