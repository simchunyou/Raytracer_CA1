#include <iostream>
#include <ngl/Colour.h>
#include "Material.h"

//Constructor and Destructor
Material::Material()
{
  colour = ngl::Colour(0.5,0.5,0.5,1);
  reflectivity = 0;
  specular = 0;
  refraction = 0;
  refractiveIndex = 1.0f;
}
Material::Material(ngl::Colour colour, float reflectivity, float specular, float refractivity, float refractiveIndex)
{
  this -> colour = colour;
  this -> reflectivity = reflectivity;
  this -> specular = specular;
  this -> refraction = reflectivity;
  this -> refractiveIndex = refractiveIndex;
}
Material::~Material()
{

}

//Getter function
ngl::Colour Material::getColour()
{
  return colour;
}
float Material::getReflectivity()
{
  return reflectivity;
}
int Material::getSpecular()
{
  return specular;
}
float Material::getRefractivity()
{
  return refraction;
}

float Material::getRefractiveIndex()
{
  return refractiveIndex;
}

//Setter function
void Material::setColour(ngl::Colour colour)
{
  this -> colour = colour;
}
void Material::setReflectivity(float reflectivity)
{
  this -> reflectivity = reflectivity;
}
void Material::setSpecular(int specular)
{
  this -> specular = specular;
}
void Material::setRefractivity(float refractivity)
{
  this ->refraction = refractivity;
}
void Material::setRefractiveIndex(float refractiveIndex)
{
  this -> refractiveIndex = refractiveIndex;
}
