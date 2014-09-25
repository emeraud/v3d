#ifndef BRDF_HPP
#define BRDF_HPP

#include "Vec3D.h"
#include "Light.hpp"
#include "Material.hpp"

class Light;

class BRDF
{
  public:
    inline static void getColor(const Vec3Df camPos,
                           const Vec3Df objPos, const Vec3Df objNormal,
                           const Material material,
                           const std::vector<Light>& lights,
                           Vec3Df &c) {
    c[0] = 0.f;
    c[1] = 0.f;
    c[2] = 0.f;

    Vec3Df pointToViewer = camPos - objPos;
    pointToViewer.normalize();

    for(unsigned int i=0; i<lights.size(); i++) {
      Vec3Df pointToLight = lights[i].getPos() - objPos;
      pointToLight.normalize();

      Vec3Df reflectedPointToLight = (2 * Vec3Df::dotProduct(pointToLight, objNormal)) * objNormal - pointToLight;
      reflectedPointToLight.normalize();

      c = (material.getDiffuse() * Vec3Df::dotProduct(pointToLight, objNormal)
                  + material.getSpecular() * pow(Vec3Df::dotProduct(reflectedPointToLight, pointToViewer), 20))
              * material.getColor();

      c = 255 * c;
    }
  }

  private:
    BRDF();
};

#endif // BRDF_HPP
