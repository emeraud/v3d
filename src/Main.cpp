#include <iostream>
#include <chrono>

#include <SDL/SDL.h>

#include "Viewer.hpp"
#include "AnimationManager.hpp"
#include "Connector3D.hpp"
#include "Scene3D.hpp"
#include "Object3D.hpp"
#include "Light.hpp"
#include "Vec3D.h"

void classicDisplay();
void configure_classic(AnimationManager&);
void bench();
void playBench(AnimationManager&);
void configure_bench1(AnimationManager&);
void configure_bench2(AnimationManager&);
void configure_bench3(AnimationManager&);

int main(int argc, char *argv[])
{
  // print args
  for (int i=0; i<argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  if (argc <= 1) {
    classicDisplay();
  } else {
    bench();
  }

  return EXIT_SUCCESS;
}

void classicDisplay() {
  // let's move it on
  Viewer viewer;
  AnimationManager animationManager(&viewer);
  configure_classic(animationManager);
  animationManager.run();
}

void configure_classic(AnimationManager &animationManager) {
  animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/ram.off")));
}

void bench() {
  {
    Viewer viewer;
    AnimationManager animationManager(&viewer);
    configure_bench1(animationManager);
    playBench(animationManager);
  }

  {
    Viewer viewer;
    AnimationManager animationManager(&viewer);
    configure_bench2(animationManager);
    playBench(animationManager);
  }

  {
    Viewer viewer;
    AnimationManager animationManager(&viewer);
    configure_bench3(animationManager);
    playBench(animationManager);
  }
}

void playBench(AnimationManager& animationManager) {
  std::cout << "Now running" << std::endl;
  auto start = std::chrono::system_clock::now();
  animationManager.run();
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << elapsed.count() << " ms" << std::endl;
}

void configure_bench1(AnimationManager &animationManager) {
  animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/ram.off")));
  animationManager.setNbFrames(5);
}

void configure_bench2(AnimationManager &animationManager) {
  animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/bunny.off")));
  animationManager.setNbFrames(3);
}

void configure_bench3(AnimationManager &animationManager) {
  animationManager.getScene().addLight(Light(Vec3Df(2.f, 2.f, 2.f), Vec3Df(1.f, 1.f, 1.f), 1.f));
  animationManager.getScene().addObject(new Object3D(Connector3D::parseFile("/home/val/Documents/dev/3d/raytracer/models/monkey.off")));
  animationManager.setNbFrames(4);
}

