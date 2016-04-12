#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "Ray.h"

//Constructor and Destructor
Ray::Ray()
{
  origin = ngl::Vec3(0,0,0);
  direction = ngl::Vec3(0,0,1);
  medium = 1.0f;
}

Ray::Ray(ngl::Vec3 origin, ngl::Vec3 direction)
{
  this -> origin = origin;
  this -> direction = direction;
  medium = 1.0f;
}

Ray::Ray(ngl::Vec4 origin, ngl::Vec4 direction)
{
  this -> origin = origin;
  this -> direction = direction;
  medium = 1.0f;
}
Ray::~Ray()
{
  //std::cout << "Ray has been deleted" << std::endl;
}

//Getter function
ngl::Vec3 Ray::getOrigin()
{
  return origin;
}
ngl::Vec3 Ray::getDirection()
{
  direction.normalize();
  return direction;
}
float Ray::getMedium()
{
  return medium;
}

//Setter function
void Ray::setOrigin(ngl::Vec3 origin)
{
  this -> origin = origin;
}
void Ray::setDirection(ngl::Vec3 direction)
{
  this -> direction = direction;
}
void Ray::setMedium(float medium)
{
  this -> medium = medium;
}
