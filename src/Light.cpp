#include <iostream>
#include "ngl/Colour.h"
#include "ngl/Vec3.h"
#include "Light.h"

//Constructor and Destructor
Light::Light()
{
  position = ngl::Vec3(0,0,0);
  colour = ngl::Colour(1,1,1,1);
  intensity = 1;
}

Light::Light(ngl::Vec3 p, ngl::Colour c, float i)
{
  position = p;
  colour = c;
  intensity = i;
}

Light::~Light()
{

}

//Getter function
ngl::Vec3 Light::getPosition()
{
  return position;
}
ngl::Colour Light::getColour()
{
  return colour;
}

float Light::getIntensity()
{
  return intensity;
}

//Setter function
void Light::setPosition(ngl::Vec3 p)
{
  position = p;
}
void Light::setColour(ngl::Colour c)
{
  colour = c;
}
void Light::setIntensity(float i)
{
  intensity = i;
}
