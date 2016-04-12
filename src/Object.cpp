#include <iostream>
#include "Ray.h"
#include "Material.h"
#include <ngl/Colour.h>
#include "Object.h"

//Constructor and Destructor
Object::Object()
{
  material = Material(ngl::Colour(0.5,0.5,0.5,1), 0, 0, 0, 1.0);
}
Object::Object(Material material)
{
  this -> material = material;
}
Object::~Object()
{

}

//Getter function
Material Object::getMaterial()
{
  return material;
}

ngl::Vec3 Object::getPosition()
{
  return position;
}

ngl::Vec3 Object::getNormalAt(ngl::Vec3 point)
{
  return ngl::Vec3(0,1,0);
}

//Setter function
void Object::assignMaterial(Material material)
{
  this -> material = material;
}

void Object:: setPosition(ngl::Vec3 p)
{
  position = p;
}

//Method function
float Object::findIntersection(Ray ray, ngl::Mat4 ViewMatrix, bool reverseNormal)
{
  return -1;
}
