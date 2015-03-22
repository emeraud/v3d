#include <iostream>
#include <string>
#include <map>
#include <chrono>

#include "Model.hpp"
#include "ModelHelper.hpp"
#include "AnimationManager.hpp"


#undef main // SDL...

void play(Model* model);

int main(int argc, char *argv[]) {
  std::map<std::string,Model*> availableScenes = ModelHelper::getModels(); 

  if (argc == 3) {
    if (std::string(argv[1]).compare("play") == 0) {
      if (availableScenes.count(std::string(argv[2])) == 1) {
        play(availableScenes[std::string(argv[2])]);
      } else {
        std::cout << "Scene: '" << argv[2] << "' not found" << std::endl;
        std::cout << "Available scenes:" << std::endl;
        for (std::map<std::string,Model*>::iterator it=availableScenes.begin();
              it != availableScenes.end(); ++it) {
          std::cout << "... " << it->first << std::endl;
        }
      }
    } else {
      std::cout << "Command: '" << argv[1] << "' not recognized" << std::endl;
    }
  } else if (argc == 2) {
    if (std::string(argv[1]).compare("bench") == 0) {
      for(std::map<std::string,Model*>::const_iterator it = availableScenes.begin(); it!=availableScenes.end(); ++it) {
        std::cout << "Playing scene '" << it->first << "'" << std::endl;
        play(it->second);
      }
    } else if (std::string(argv[1]).compare("play") == 0) {
      std::cout << "Available scenes:" << std::endl;
      for (std::map<std::string,Model*>::iterator it=availableScenes.begin();
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
    play(availableScenes["Bunny_40Frames"]); 
  }

  for(std::map<std::string,Model*>::const_iterator it = availableScenes.begin(); it!=availableScenes.end(); ++it) {
    delete it->second;
  }

  return EXIT_SUCCESS;
}

void play(Model* model) {
  model->prepare();
  AnimationManager* animationManager = new AnimationManager(model); 
  if (model->isBenchActivated()) {
    std::cout << "Now running" << std::endl;
    auto start = std::chrono::system_clock::now();
    animationManager->run();
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << " ms" << std::endl;
  } else {
    animationManager->run();
  }
  delete animationManager;
}
