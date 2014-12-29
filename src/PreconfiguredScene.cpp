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

void Scene_Primitives::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(5.f, 5.f, 5.f), Vec3Df(1.f, 1.f, 1.f), 1.f));

  Object3D* plan1 = new PlanObject3D(Vec3Df(0.f, 0.f, 0.f), Vec3Df(0.f, 0.f, 1.f));
  Object3D* sphere1 = new SphereObject3D(Vec3Df(1.5, 0.8, 0.5f), 0.5f);
  Object3D* sphere2 = new SphereObject3D(Vec3Df(-0.5, -0.5, 0.5f), 0.5f);
  Object3D* sphere3 = new SphereObject3D(Vec3Df(0.5f, 0.5f, 0.5f), 0.5f);

  sphere1->setMaterial(Material(1.f, 1000.f, Vec3Df (1.f, 0.6f, 0.2f)));
  sphere2->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.6f, 0.7f)));
  sphere3->setMaterial(Material(0.7f, 1000.f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _animationManager->getScene().addObject(plan1);
  _animationManager->getScene().addObject(sphere1);
  _animationManager->getScene().addObject(sphere2);
  _animationManager->getScene().addObject(sphere3);
  _animationManager->setNbFrames(60);
  _activateBench = true;
}

void Scene_Ram_5Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new MeshObject3D(getRam()));
  _animationManager->setNbFrames(5);
  _activateBench = true;
}

void Scene_Bunny_3Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new MeshObject3D(getBunny()));
  _animationManager->setNbFrames(3);
  _activateBench = true;
}

void Scene_Bunny_10Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new MeshObject3D(getBunny()));
  _animationManager->setNbFrames(10);
  _activateBench = true;
}

void Scene_Bunny_40Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(-2.f, -2.f, -2.f), Vec3Df(0.f, 0.f, 1.f), 1.f));
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 0.f, -2.f), Vec3Df(1.f, 0.f,0.f), 1.f));
  _animationManager->getScene().addObject(new MeshObject3D(getBunny()));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Monkey_4Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new MeshObject3D(getMonkey()));
  _animationManager->setNbFrames(4);
  _activateBench = true;
}

void Scene_MonkeyAndBunny_40Frames::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addLight(Light(Vec3Df(0.1f, 0.0f, 0.5f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _animationManager->getScene().addObject(new MeshObject3D(getMonkey()));
  _animationManager->getScene().addObject(new MeshObject3D(getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Nightclub::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(0.f, 1.f, 1.f), 0.8f));
  _animationManager->getScene().addLight(Light(Vec3Df(-2.1f, 0.0f, 1.5f), Vec3Df(1.f, 0.f, 1.f), 0.2f));
  _animationManager->getScene().addObject(new MeshObject3D(getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _animationManager->getScene().addObject(new MeshObject3D(getGround(), Vec3Df(1.f,0.5f,0.f)));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Animals::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.0f));

  Object3D* ground = new PlanObject3D(Vec3Df(0.f, 0.f, 0.f), Vec3Df(0.f, 0.f, 1.f));
  Object3D* ram = new MeshObject3D(getRam(), Vec3Df(1.f, 0.5f, 0.0f));
  Object3D* rhino = new MeshObject3D(getRhino(), Vec3Df(-1.f, -1.f, 0.4f));
  Object3D* gargoyle = new MeshObject3D(getGargoyle(), Vec3Df(-1.f, 1.f, 0.1f));

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

void Scene_Animals_2Lights::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(0.59f, 0.25f, 0.4f), 1.0f));
  _animationManager->getScene().addLight(Light(Vec3Df(1.f, 0.5f, 10.f), Vec3Df(0.39f, 0.25f, 0.4f), 1.0f));

  Object3D* ground = new MeshObject3D(getGround());
  Object3D* ram = new MeshObject3D(getRam(), Vec3Df(1.f, 0.5f, 0.0f));
  Object3D* rhino = new MeshObject3D(getRhino(), Vec3Df(-1.f, -1.f, 0.4f));
  Object3D* gargoyle = new MeshObject3D(getGargoyle(), Vec3Df(-1.f, 1.f, 0.1f));

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
  _animationManager->getScene().addObject(new MeshObject3D(getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _animationManager->getScene().addObject(new MeshObject3D(getRam(), Vec3Df(1.f, 0.5f, 0.9f)));
  _animationManager->getScene().addObject(new MeshObject3D(getGround(), Vec3Df(1.f,0.5f,0.f)));
  _animationManager->setNbFrames(40);
  _activateBench = true;
}

void Scene_Room::_configure() {
  _animationManager->getScene().addLight(Light(Vec3Df(0.9f, 0.3f, 0.7f), Vec3Df(1.f, 1.f, 1.f), 1.f));

  Object3D* plan1 = new PlanObject3D(Vec3Df(0.f, 0.f, 0.f), Vec3Df(0.f, 0.f, 1.f));
  Object3D* plan2 = new PlanObject3D(Vec3Df(0.f, 10.f, 0.f), Vec3Df(0.f, -1.f, 0.f));
  Object3D* plan3 = new PlanObject3D(Vec3Df(10.f, 0.f, 0.f), Vec3Df(-1.f, 0.f, 0.f));
  Object3D* plan4 = new PlanObject3D(Vec3Df(0.f, -10.f, 0.f), Vec3Df(0.f, 1.f, 0.f));
  Object3D* plan5 = new PlanObject3D(Vec3Df(-10.f, 0.f, 0.f), Vec3Df(1.f, 0.f, 0.f));

  Object3D* sphere1 = new SphereObject3D(Vec3Df(0.0f, 0.0f, 0.5f), 0.5f);

  plan1->setMaterial(Material(1.f, 1000.f, Vec3Df (1.f, 0.6f, 0.2f)));
  plan2->setMaterial(Material(1.f, 1000.f, Vec3Df (1.f, 0.4f, 0.2f)));
  plan3->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  plan4->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  plan5->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  sphere1->setMaterial(Material(0.7f, 1000.f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _animationManager->getScene().addObject(plan1);
  _animationManager->getScene().addObject(plan2);
  _animationManager->getScene().addObject(plan3);
  _animationManager->getScene().addObject(plan4);
  _animationManager->getScene().addObject(plan5);
  _animationManager->getScene().addObject(sphere1);
  _animationManager->setNbFrames(30);
  _activateBench = true;
}

