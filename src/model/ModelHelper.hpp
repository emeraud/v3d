#ifndef MODELHELPER_HPP
#define MODELHELPER_HPP

#include <string>
#include <map>

class Model;

class ModelHelper {
  public:
    // caller is responsible for allocated objects lifecycle
    static std::map<std::string,Model*> getModels();
};

#endif
