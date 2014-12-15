#include "PreconfiguredScene.hpp"

#include <chrono>

#include "Object3D.hpp"
#include "Tessellation3D.hpp"

PreconfiguredScene::PreconfiguredScene() : _activateBench(false) {
  
}

void PreconfiguredScene::play() {
  _viewer = new Viewer();
  _animationManager = new AnimationManager(_viewer), 
  _configure();
  _animationManager->getScene().prepare();
  if (_activateBench) {
    _playWithBench();
  } else {
    _play();
  }
  delete _viewer;
  delete _animationManager;
}

void PreconfiguredScene::_play() {
  _animationManager->run();
}

void PreconfiguredScene::_playWithBench() {
  std::cout << "Now running" << std::endl;
  auto start = std::chrono::system_clock::now();
  _play();
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << elapsed.count() << " ms" << std::endl;
}

Tessellation3D* PreconfiguredScene::buildTessellation(std::string path) {
  return Connector3D::parseFile(path.c_str());
}

Tessellation3D* PreconfiguredScene::getRam() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/ram.off");
}

Tessellation3D* PreconfiguredScene::getBunny() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/bunny.off");
}

Tessellation3D* PreconfiguredScene::getMonkey() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/monkey.off");
}

Tessellation3D* PreconfiguredScene::getRhino() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/rhino.off");
}

Tessellation3D* PreconfiguredScene::getGargoyle() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/gargoyle.off");
}

Tessellation3D* PreconfiguredScene::getGround() {
  return buildTessellation("/home/val/Documents/dev/v3d/models/ground.off");
}

void Scene_Ram_5Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new Object3D(getRam()));
  _animationManager->setNbFrames(5);
  _activateBench = true;
}

void Scene_Bunny_3Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new Object3D(getBunny()));
  _animationManager->setNbFrames(3);
  _activateBench = true;
}

void Scene_Bunny_10Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new Object3D(getBunny()));
  _animationManager->setNbFrames(10);
  _activateBench = true;
}

void Scene_Bunny_40Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(-2.f, -2.f, -2.f), Vec3Df(0.f, 0.f, 1.f), 1.f));
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 0.f, -2.f), Vec3Df(1.f, 0.f,0.f), 1.f));
  _animationManager->getScene().addObject(new Object3D(getBunny()));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Monkey_4Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new Object3D(getMonkey()));
  _animationManager->setNbFrames(4);
  _activateBench = true;
}

void Scene_MonkeyAndBunny_40Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addLight(Light(Vec3Df(0.1f, 0.0f, 0.5f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new Object3D(getMonkey()));
  _animationManager->getScene().addObject(new Object3D(getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Nightclub::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(0.f, 1.f, 1.f), 0.8f));
  _animationManager->getScene().addLight(Light(Vec3Df(-2.1f, 0.0f, 1.5f), Vec3Df(1.f, 0.f, 1.f), 0.2f));
  _animationManager->getScene().addObject(new Object3D(getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _animationManager->getScene().addObject(new Object3D(getGround(), Vec3Df(1.f,0.5f,0.f)));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Animals::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.0f));

  Object3D* ground = new Object3D(getGround());
  Object3D* ram = new Object3D(getRam(), Vec3Df(1.f, 0.5f, 0.0f));
  Object3D* rhino = new Object3D(getRhino(), Vec3Df(-1.f, -1.f, 0.4f));
  Object3D* gargoyle = new Object3D(getGargoyle(), Vec3Df(-1.f, 1.f, 0.1f));

  ram->setMaterial(Material(1.f, 1.f, Vec3Df (1.f, 0.6f, 0.2f)));
  rhino->setMaterial(Material(1.0f, 0.2f, Vec3Df (0.6f, 0.6f, 0.7f)));
  gargoyle->setMaterial(Material(0.7f, 0.4f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _animationManager->getScene().addObject(ground);
  _animationManager->getScene().addObject(ram);
  _animationManager->getScene().addObject(rhino);
  _animationManager->getScene().addObject(gargoyle);
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_test::_configure() {
//  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.0f));
  _animationManager->getScene().addLight(Light(Vec3Df(-2.1f, 0.0f, 1.5f), Vec3Df(1.f, 1.f, 1.f), 1.0f));
  _animationManager->getScene().addObject(new Object3D(getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _animationManager->getScene().addObject(new Object3D(getRam(), Vec3Df(1.f, 0.5f, 0.9f)));
  _animationManager->getScene().addObject(new Object3D(getGround(), Vec3Df(1.f,0.5f,0.f)));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

