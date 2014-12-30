#include "ModelScenesHelper.hpp"

#include "Object3D.hpp"
#include "Scene3D.hpp"
#include "Camera.hpp"

#include "Light.hpp"
#include "Material.hpp"

#include "ModelObjectsHelper.hpp"


void Scene_Primitives::_configure() {
  _scene->addLight(Light(Vec3Df(5.f, 5.f, 5.f), Vec3Df(1.f, 1.f, 1.f), 1.f));

  Object3D* plan1 = new PlanObject3D(Vec3Df(0.f, 0.f, 0.f), Vec3Df(0.f, 0.f, 1.f));
  Object3D* sphere1 = new SphereObject3D(Vec3Df(1.5, 0.8, 0.5f), 0.5f);
  Object3D* sphere2 = new SphereObject3D(Vec3Df(-0.5, -0.5, 0.5f), 0.5f);
  Object3D* sphere3 = new SphereObject3D(Vec3Df(0.5f, 0.5f, 0.5f), 0.5f);

  sphere1->setMaterial(Material(1.f, 1000.f, Vec3Df (1.f, 0.6f, 0.2f)));
  sphere2->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.6f, 0.7f)));
  sphere3->setMaterial(Material(0.7f, 1000.f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _scene->addObject(plan1);
  _scene->addObject(sphere1);
  _scene->addObject(sphere2);
  _scene->addObject(sphere3);
  _nbFrames = 60;
  _activateBench = true;
}

void Scene_Ram_5Frames::_configure() {
  _scene->addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getRam()));
  _nbFrames = 5;
  _activateBench = true;
}

void Scene_Bunny_3Frames::_configure() {
  _scene->addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getBunny()));
  _nbFrames = 3;
  _activateBench = true;
}

void Scene_Bunny_10Frames::_configure() {
  _scene->addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getBunny()));
  _nbFrames = 10;
  _activateBench = true;
}

void Scene_Bunny_40Frames::_configure() {
  _scene->addLight(Light(Vec3Df(-2.f, -2.f, -2.f), Vec3Df(0.f, 0.f, 1.f), 1.f));
  _scene->addLight(Light(Vec3Df(2.f, 0.f, -2.f), Vec3Df(1.f, 0.f,0.f), 1.f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getBunny()));
  _nbFrames = 40;
  _activateBench = true;
}

void Scene_Monkey_4Frames::_configure() {
  _scene->addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getMonkey()));
  _nbFrames = 4;
  _activateBench = true;
}

void Scene_MonkeyAndBunny_40Frames::_configure() {
  _scene->addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene->addLight(Light(Vec3Df(0.1f, 0.0f, 0.5f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getMonkey()));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _nbFrames = 40;
  _activateBench = true;
}

void Scene_Nightclub::_configure() {
  _scene->addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(0.f, 1.f, 1.f), 0.8f));
  _scene->addLight(Light(Vec3Df(-2.1f, 0.0f, 1.5f), Vec3Df(1.f, 0.f, 1.f), 0.2f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getGround(), Vec3Df(1.f,0.5f,0.f)));
  _nbFrames = 40;
  _activateBench = true;
}

void Scene_Animals::_configure() {
  _scene->addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.0f));

  Object3D* ground = new PlanObject3D(Vec3Df(0.f, 0.f, 0.f), Vec3Df(0.f, 0.f, 1.f));
  Object3D* ram = new MeshObject3D(ModelObjectsHelper::getRam(), Vec3Df(1.f, 0.5f, 0.0f));
  Object3D* rhino = new MeshObject3D(ModelObjectsHelper::getRhino(), Vec3Df(-1.f, -1.f, 0.4f));
  Object3D* gargoyle = new MeshObject3D(ModelObjectsHelper::getGargoyle(), Vec3Df(-1.f, 1.f, 0.1f));

  ram->setMaterial(Material(1.f, 1.f, Vec3Df (1.f, 0.6f, 0.2f)));
  rhino->setMaterial(Material(1.0f, 0.2f, Vec3Df (0.6f, 0.6f, 0.7f)));
  gargoyle->setMaterial(Material(0.7f, 0.4f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _scene->addObject(ground);
  _scene->addObject(ram);
  _scene->addObject(rhino);
  _scene->addObject(gargoyle);
  _nbFrames = 40;
  _activateBench = true;
}

void Scene_Animals::_move(float t) {
  _camera->setPos(Vec3Df(5.f * cos(t * 2.f * PI), 5.f * sin(t * 2.f * PI), 7.f - 6.f*t));
  _camera->setDir(-1.f * _camera->getPos());
  _camera->setUp(Vec3Df(0.f, 0.f, 1.f));
  _camera->setRight(Vec3Df::crossProduct(_camera->getDir(), _camera->getUp()));
}


void Scene_Animals_2Lights::_configure() {
  _scene->addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(0.59f, 0.25f, 0.4f), 1.0f));
  _scene->addLight(Light(Vec3Df(1.f, 0.5f, 10.f), Vec3Df(0.39f, 0.25f, 0.4f), 1.0f));

  Object3D* ground = new MeshObject3D(ModelObjectsHelper::getGround());
  Object3D* ram = new MeshObject3D(ModelObjectsHelper::getRam(), Vec3Df(1.f, 0.5f, 0.0f));
  Object3D* rhino = new MeshObject3D(ModelObjectsHelper::getRhino(), Vec3Df(-1.f, -1.f, 0.4f));
  Object3D* gargoyle = new MeshObject3D(ModelObjectsHelper::getGargoyle(), Vec3Df(-1.f, 1.f, 0.1f));

  ram->setMaterial(Material(1.f, 1.f, Vec3Df (1.f, 0.6f, 0.2f)));
  rhino->setMaterial(Material(1.0f, 0.2f, Vec3Df (0.6f, 0.6f, 0.7f)));
  gargoyle->setMaterial(Material(0.7f, 0.4f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _scene->addObject(ground);
  _scene->addObject(ram);
  _scene->addObject(rhino);
  _scene->addObject(gargoyle);
  _nbFrames = 40;
  _activateBench = true;
}

void Scene_test::_configure() {
//  _scene->addLight(Light(Vec3Df(3.f, 3.f, 3.f), Vec3Df(1.f, 1.f, 1.f), 1.0f));
  _scene->addLight(Light(Vec3Df(-2.1f, 0.0f, 1.5f), Vec3Df(1.f, 1.f, 1.f), 1.0f));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getBunny(), Vec3Df(0.f, 0.f, 0.9f)));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getRam(), Vec3Df(1.f, 0.5f, 0.9f)));
  _scene->addObject(new MeshObject3D(ModelObjectsHelper::getGround(), Vec3Df(1.f,0.5f,0.f)));
  _nbFrames = 40;
  _activateBench = true;
}

void Scene_Room::_configure() {
  _scene->addLight(Light(Vec3Df(0.9f, 0.3f, 0.7f), Vec3Df(1.f, 1.f, 1.f), 1.f));

  Object3D* plan1 = new PlanObject3D(Vec3Df(0.f, 0.f, 0.f), Vec3Df(0.f, 0.f, 1.f));
  Object3D* plan2 = new PlanObject3D(Vec3Df(0.f, 10.f, 0.f), Vec3Df(0.f, -1.f, 0.f));
  Object3D* plan3 = new PlanObject3D(Vec3Df(10.f, 0.f, 0.f), Vec3Df(-1.f, 0.f, 0.f));
  Object3D* plan4 = new PlanObject3D(Vec3Df(0.f, -10.f, 0.f), Vec3Df(0.f, 1.f, 0.f));
  Object3D* plan5 = new PlanObject3D(Vec3Df(-10.f, 0.f, 0.f), Vec3Df(1.f, 0.f, 0.f));
  Object3D* plan6 = new PlanObject3D(Vec3Df(0.f, 0.f, 7.f), Vec3Df(0.f, 0.f, -1.f));

  Object3D* sphere1 = new SphereObject3D(Vec3Df(0.0f, 0.0f, 0.5f), 0.5f);

  plan1->setMaterial(Material(1.f, 1000.f, Vec3Df (1.f, 0.6f, 0.2f)));
  plan2->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  plan3->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  plan4->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  plan5->setMaterial(Material(1.f, 1000.f, Vec3Df (0.6f, 0.4f, 0.7f)));
  plan6->setMaterial(Material(1.f, 1000.f, Vec3Df (1.f, 0.6f, 0.2f)));
  sphere1->setMaterial(Material(0.7f, 1000.f, Vec3Df (0.5f, 0.8f, 0.5f)));

  _scene->addObject(plan1);
  _scene->addObject(plan2);
  _scene->addObject(plan3);
  _scene->addObject(plan4);
  _scene->addObject(plan5);
  _scene->addObject(plan6);
  _scene->addObject(sphere1);
  _nbFrames = 60;
  _activateBench = true;
}

