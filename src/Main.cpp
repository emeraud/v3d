#include <iostream>
#include <string>
#include <map>

#include "PreconfiguredScene.hpp"

int main(int argc, char *argv[]) {
  std::map<std::string,PreconfiguredScene*> availableScenes; 
  availableScenes["Primitives"] = new Scene_Primitives(); 
  availableScenes["Ram_5Frames"] = new Scene_Ram_5Frames(); 
  availableScenes["Bunny_3Frames"] = new Scene_Bunny_3Frames(); 
  availableScenes["Bunny_10Frames"] = new Scene_Bunny_10Frames(); 
  availableScenes["Bunny_40Frames"] = new Scene_Bunny_40Frames(); 
  availableScenes["Monkey_4Frames"] = new Scene_Monkey_4Frames(); 
  availableScenes["MonkeyAndBunny_40Frames"] = new Scene_MonkeyAndBunny_40Frames(); 
  availableScenes["Nightclub"] = new Scene_Nightclub(); 
  availableScenes["Animals"] = new Scene_Animals(); 
  availableScenes["Animals_2Lights"] = new Scene_Animals_2Lights(); 
  availableScenes["Room"] = new Scene_Room(); 
  availableScenes["test"] = new Scene_test(); 

  if (argc == 3) {
    if (std::string(argv[1]).compare("play") == 0) {
      if (availableScenes.count(std::string(argv[2])) == 1) {
        availableScenes[std::string(argv[2])]->play();
      } else {
        std::cout << "Scene: '" << argv[2] << "' not found" << std::endl;
        std::cout << "Available scenes:" << std::endl;
        for (std::map<std::string,PreconfiguredScene*>::iterator it=availableScenes.begin();
              it != availableScenes.end(); ++it) {
          std::cout << "... " << it->first << std::endl;
        }
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
    } else if (std::string(argv[1]).compare("play") == 0) {
      std::cout << "Available scenes:" << std::endl;
      for (std::map<std::string,PreconfiguredScene*>::iterator it=availableScenes.begin();
            it != availableScenes.end(); ++it) {
        std::cout << "... " << it->first << std::endl;
      }
    } else {
      std::cout << "Command: '" << argv[1] << "' not recognized" << std::endl;
      std::cout << "Available commands:" << std::endl;
      std::cout << "... bench" << std::endl;
      std::cout << "... play" << std::endl;
    }
  } else {
    availableScenes["Ram_5Frames"]->play(); 
  }

  for(std::map<std::string,PreconfiguredScene*>::const_iterator it = availableScenes.begin(); it!=availableScenes.end(); ++it) {
    //std::cout << "Releasing scene '" << it->first << "'" << std::endl;
    delete it->second;
  }

  return EXIT_SUCCESS;
}

