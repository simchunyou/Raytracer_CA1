#ifndef __LIGHT_H
#define __LIGHT_H
#include "ngl/Vec3.h"
#include "ngl/Colour.h"

class Light
{
  private:
    ngl::Vec3 position;
    ngl::Colour colour;
    float intensity;

  public:
    //Constructor and Destructor
    Light();
    Light(ngl::Vec3 p, ngl::Colour c, float i);
    ~Light();

    //Getter function
    ngl::Vec3 getPosition();
    ngl::Colour getColour();
    float getIntensity();

    //Setter function
    void setPosition(ngl::Vec3 p);
    void setColour(ngl::Colour c);
    void setIntensity(float i);
};

#endif
