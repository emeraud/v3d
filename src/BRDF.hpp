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
      
      Vec3Df pointToCam = camPos - objPos;
      pointToCam.normalize();

      c = Vec3Df(0.f, 0.f, 0.f);

      for (UInt i=0; i<lights.size(); i++) {
        Vec3Df pointToLight = lights[i].getPos() - objPos;
        pointToLight.normalize();

        // diffuse part (calculate the cosine between normal and light direction)
        float dot = Vec3Df::dotProduct(objNormal,pointToLight);
        dot = dot > 0.f ? dot : 0.f; // dot < 0: light at the wrong place
        c += material.getColor() * lights[i].getColor() * dot * material.getDiffuse();

        // specular part
        Vec3Df blinn = pointToLight + pointToCam;
        float temp = Vec3Df::dotProduct(blinn,blinn);
        if ((temp > 0.f && temp > EPSILON) || (temp < 0.f && temp < EPSILON)) {
          temp = sqrt(temp);
          blinn = (1.f/temp) * blinn;
          float blinnTerm = Vec3Df::dotProduct(blinn,objNormal);
          blinnTerm = blinnTerm > 0.f ? blinnTerm : 0.f;
          c += pow(blinnTerm,material.getSpecular()) * blinnTerm * material.getColor() * lights[i].getColor();
        }
      }

      c = c*255;
    }

  private:
    BRDF();
};

#endif // BRDF_HPP
