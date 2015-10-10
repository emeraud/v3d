#ifndef MODELOBJECTSHELPER_HPP
#define MODELOBJECTSHELPER_HPP

#include <string>

class Tessellation3D;

class ModelObjectsHelper {
  public:
    static Tessellation3D* getRam();
    static Tessellation3D* getBunny();
    static Tessellation3D* getMonkey();
    static Tessellation3D* getRhino();
    static Tessellation3D* getGargoyle();
    static Tessellation3D* getGround();
	static Tessellation3D* getTeapot();

    static Tessellation3D* buildTessellation(std::string path);
};

#endif

