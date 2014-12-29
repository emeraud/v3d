#ifndef SCENE3D_HPP
#define SCENE3D_HPP

#include <vector>

#include "Object3D.hpp"
#include "Light.hpp"

class Scene3D {
  public:
    Scene3D();
    ~Scene3D();

  public:
    void addObject(Object3D* object);
    void addLight(Light light);
    std::vector<const Object3D*> getObjects();
    std::vector<Light> getLights();
    void prepare(); // normalize light intensities

  public:
    bool getIntersected(const Ray& ray, Vec3Df& intersectionPoint, Vec3Df& intersectionNormal, const Object3D* &object) const;
    bool isShadow(const Ray& ray, const Object3D* &object, float sqMaxLength) const;

  private:
    std::vector<Object3D*>      _objects;
    std::vector<Light>          _lights;
};

#endif
