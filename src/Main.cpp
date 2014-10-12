#include <iostream>
#include <chrono>
#include <string>
#include <map>

#include <SDL/SDL.h>

#include "Viewer.hpp"
#include "AnimationManager.hpp"
#include "Connector3D.hpp"
#include "Scene3D.hpp"
#include "Object3D.hpp"
#include "Light.hpp"
#include "Vec3D.h"

#include "PreconfiguredScene.hpp"

int main(int argc, char *argv[]) {
  std::map<std::string,PreconfiguredScene*> availableScenes; 
  availableScenes["Ram_5Frames"] = new Scene_Ram_5Frames(); 
  availableScenes["Bunny_3Frames"] = new Scene_Bunny_3Frames(); 
  availableScenes["Bunny_10Frames"] = new Scene_Bunny_10Frames(); 
  availableScenes["Bunny_40Frames"] = new Scene_Bunny_40Frames(); 
  availableScenes["Monkey_4Frames"] = new Scene_Monkey_4Frames(); 

  if (argc == 3) {
    if (std::string(argv[1]).compare("play") == 0) {
      if (availableScenes.count(std::string(argv[2])) == 1) {
        availableScenes[std::string(argv[2])]->play();
      } else {
        std::cout << "Scene: '" << argv[2] << "' not found" << std::endl;
      }
    } else {
      std::cout << "Command: '" << argv[1] << "' not recognized" << std::endl;
    }
  } else if (argc == 2) {
    if (std::string(argv[1]).compare("bench") == 0) {
      for(std::map<std::string,PreconfiguredScene*>::const_iterator it = availableScenes.begin(); it!=availableScenes.end(); ++it) {
        std::cout << "Playing scene '" << it->first << "'" << std::endl;
        it->second->play();
      }
    } else {
      std::cout << "Command: '" << argv[1] << "' not recognized" << std::endl;
    }
  } else {
    availableScenes["Ram_5Frames"]->play(); 
  }

  for(std::map<std::string,PreconfiguredScene*>::const_iterator it = availableScenes.begin(); it!=availableScenes.end(); ++it) {
    std::cout << "Releasing scene '" << it->first << "'" << std::endl;
    delete it->second;
  }

  return EXIT_SUCCESS;
}

