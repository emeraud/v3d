#ifndef MODELSCENESHELPER_HPP
#define MODELSCENESHELPER_HPP

#include "Model.hpp"

class Scene_Primitives : public Model {
  protected:
    virtual void _configure();
};

class Scene_Ram_5Frames : public Model {
  protected:
    virtual void _configure();
};

class Scene_Bunny_3Frames : public Model {
  protected:
    virtual void _configure();
};

class Scene_Bunny_10Frames : public Model {
  protected:
    virtual void _configure();
};

class Scene_Bunny_40Frames : public Model {
  protected:
    virtual void _configure();
};

class Scene_Monkey_4Frames : public Model {
  protected:
    virtual void _configure();
};

class Scene_MonkeyAndBunny_40Frames : public Model {
  protected:
    virtual void _configure();
};

class Scene_Nightclub : public Model {
  protected:
    virtual void _configure();
};

class Scene_Animals : public Model {
  protected:
    virtual void _configure();
    virtual void _move(float t);
};

class Scene_Animals_2Lights : public Model {
  protected:
    virtual void _configure();
};

class Scene_Room : public Model {
  protected:
    virtual void _configure();
};

class Scene_test : public Model {
  protected:
    virtual void _configure();
};

#endif

