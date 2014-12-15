#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

#include "Tessellation3D.hpp"
#include "KDTree.hpp"
#include "Material.hpp"

class Object3D {
  public:
    Object3D();
    Object3D(const Vec3Df &position);
    virtual ~Object3D();

  public:
    Material getMaterial() const;
    void setMaterial(const Material& material);

  public:
    virtual bool intersect(const Ray& ray, Vec3Df& intersectionPoint, Vec3Df& intersectionNormal) const;

  protected:
    Material          _material;
};

class MeshObject3D : public Object3D {
  public:
    MeshObject3D(Tessellation3D* tessellation);
    MeshObject3D(Tessellation3D* tessellation, const Vec3Df &position);
    virtual ~MeshObject3D();

  private:
    void init();

  public:
    virtual bool intersect(const Ray& ray, Vec3Df& intersectionPoint, Vec3Df& intersectionNormal) const;

  private:
    Tessellation3D*   _tessellation;
    KDTree*           _kdTree;
};

#endif
