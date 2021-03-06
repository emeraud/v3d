#include "Scene3D.hpp"

Scene3D::Scene3D() {

}

Scene3D::~Scene3D() {
  for (unsigned int i=0; i<_objects.size(); i++) {
    delete _objects[i];
  }
  _objects.resize(0);
}

void Scene3D::addObject(Object3D* object) {
  _objects.push_back(object);
}

void Scene3D::addLight(Light light) {
  _lights.push_back(light);
}

void Scene3D::prepare() {
  if (_lights.size() > 1) {
    float totalIntensity = 0.f;
    for (UInt i=0; i<_lights.size(); i++) {
      totalIntensity += _lights[i].getIntensity();
    }
    if (totalIntensity > 0.f) {
      for (UInt i=0; i<_lights.size(); i++) {
        _lights[i].setIntensity(_lights[i].getIntensity() / totalIntensity);
      }
    }
  }
}

std::vector<const Object3D*> Scene3D::getObjects() {
  std::vector<const Object3D*> objects;
  for (std::vector<Object3D*>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
    objects.push_back((*it));
  }
  return objects;
}

std::vector<Light> Scene3D::getLights() {
  std::vector<Light> lights;
  for (std::vector<Light>::const_iterator it = _lights.begin(); it != _lights.end(); ++it) {
    lights.push_back((*it));
  }
  return lights;
}

bool Scene3D::getIntersected(InterContext& interContext) const {
  float sqDist = FLT_MAX;
  float sqMinDist = FLT_MAX;

  for (std::vector<Object3D*>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
    if ((*it)->intersect(interContext)) {
      sqDist = Vec3Df::squaredDistance(interContext.tmpPoint, interContext.ray.getOrigin());
      if (sqDist < sqMinDist) {
        sqMinDist = sqDist;
        interContext.point = interContext.tmpPoint;
        interContext.normal = interContext.tmpNormal;
        interContext.normal.normalize();
        interContext.object = (*it);
      }
    }
  }

  return sqMinDist != FLT_MAX;
}


bool Scene3D::isShadow(InterContext& interContext, float sqMaxLength) const {
  for (std::vector<Object3D*>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
    if ((*it) == interContext.object) {
      // ignore source object
      continue;
    }
    if ((*it)->intersect(interContext)) {
      if (Vec3Df::squaredDistance(interContext.tmpPoint, interContext.ray.getOrigin()) < sqMaxLength) {
        return true;
      }
    }
  }
  return false;
}

