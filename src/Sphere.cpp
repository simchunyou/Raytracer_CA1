#include <iostream>
#include <ngl/Vec3.h>
#include "Sphere.h"
#include "Object.h"
#include "math.h"
#include "Ray.h"
#include <ngl/Mat4.h>
#include <ngl/Vec4.h>

//Constructor and Destructor
Sphere::Sphere()
{
  position = ngl::Vec3(0,0,0);
  radius = 1;
}

Sphere::Sphere(ngl::Vec3 p, float r)
{
  position = p;
  radius = r;
}

Sphere::~Sphere()
{
  //std::cout << "Sphere has been deleted" << std::endl;
}

//Getter function
ngl::Vec3 Sphere::getPosition()
{
  return position;
}

float Sphere::getRadius()
{
  return radius;
}

//Setter function
void Sphere::setPosition(ngl::Vec3 p)
{
  position = p;
}

void Sphere::setRadius(float r)
{
  radius = r;
}

//Method function
ngl::Vec3 Sphere::getNormalAt(ngl::Vec3 point)
{
  return point - position;
}

float Sphere::findIntersection(Ray ray, ngl::Mat4 ViewMatrix, bool reverseNormal)
{
  //For the normal is always pointing outwards from the center, the normals need not be recalculated

  //Using quadratics
  float a,b,c;

  a = ray.getDirection().dot(ray.getDirection());

  if (reverseNormal == 0)
  {
    b = (2*ray.getDirection()).dot((ray.getOrigin()-position));
  }
  else
  {
    b = (2*ray.getDirection()).dot((position-ray.getOrigin()));
  }

  c = (ray.getOrigin()-position).dot((ray.getOrigin()-position))-(radius*radius);

  float discriminant = b*b - 4*a*c;
  if (discriminant > 0)
  {
    //The ray intersects
    //The first root
    float root_1 = ((-1*b - sqrt(discriminant))/2*a) - 0.00005;
    if (root_1 > 0)
    {
      return root_1;
    }
    else
    {
      float root_2 = ((-1*b + sqrt(discriminant))/2*a) - 0.00005;
      return root_2;
    }
  }
  else
  {
    //Ray miss
    return -1;
  }
}
