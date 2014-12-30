#include "Model.hpp"

#include "Scene3D.hpp"
#include "Camera.hpp"

Model::Model() : _nbFrames(10), _activateBench(false) {
  _scene = new Scene3D(); 
  _camera = new Camera();
}

Model::~Model() {
  delete _camera;
  delete _scene;
}

Scene3D* Model::getScene() {
  _configure();
  _scene->prepare();
  return _scene;
}

Camera* Model::getCamera() {
  return _camera;
}

bool Model::isBenchActivated() {
  return _activateBench;
}

UInt Model::getNbFrames() {
  return _nbFrames;
}

void Model::updateToFrame(UInt frame) {
  if (_nbFrames > 0) {
    float t = float(frame) / float(_nbFrames);
    _move(t);
  }
}

void Model::_move(float t) {
  _camera->setPos(Vec3Df(5.f * cos(t * 2.f * PI), 5.f * sin(t * 2.f * PI), 3.f));
  _camera->setDir(-1.f * _camera->getPos());
  _camera->setUp(Vec3Df(0.f, 0.f, 1.f));
  _camera->setRight(Vec3Df::crossProduct(_camera->getDir(), _camera->getUp()));
}

