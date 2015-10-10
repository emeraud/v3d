#ifndef SCENE3D_HPP
#define SCENE3D_HPP

#include <vector>

#include "Object3D.hpp"
#include "renderer/Light.hpp"
#include "renderer/InterContext.hpp"

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
    bool getIntersected(InterContext& interContext) const;
    bool isShadow(InterContext& interContext, float sqMaxLength) const;

  private:
    std::vector<Object3D*>      _objects;
    std::vector<Light>          _lights;
};

#endif
