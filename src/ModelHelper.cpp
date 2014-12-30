#include "ModelHelper.hpp"

#include "Model.hpp"
#include "ModelScenesHelper.hpp"

std::map<std::string,Model*> ModelHelper::getModels() {
  std::map<std::string,Model*> availableScenes; 
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

  return availableScenes;
}
