#include <iostream>
#include <ngl/Vec3.h>
#include "Plane.h"
#include "math.h"
#include "Ray.h"

//Constructor and Destructor
Plane::Plane()
{
  position = ngl::Vec3(0,0,0);
  normal = ngl::Vec3 (0,1,0);
}
Plane::Plane(ngl::Vec3 p, ngl::Vec3 n)
{
  position = p;
  normal = n;
}
Plane::~Plane()
{
  //std::cout << "Plane has been deleted" << std::endl;
}

//Getter function
ngl::Vec3 Plane::getPosition()
{
  return position;
}
ngl::Vec3 Plane::getNormalAt(ngl::Vec3 point)
{
  return normal;
}

//Setter function
void Plane::setPosition(ngl::Vec3 p)
{
  position = p;
}
void Plane::setNormal(ngl::Vec3 n)
{
  normal = n;
}

//Method function
float Plane::findIntersection(Ray ray, ngl::Mat4 ViewMatrix, bool reverseNormal)
{
  //First we transform the normals based on the ViewMatrix. However, we dont move them
  //We do not need to reverse normal for refraction as a plane only can refract once.
  //Set translation for view matrix back to 0
  ViewMatrix.setAtXY(3,0,0);
  ViewMatrix.setAtXY(3,1,0);
  ViewMatrix.setAtXY(3,2,0);

  //Next we change the normal direction
  ngl::Vec4 normal_old (normal.m_x, normal.m_y, normal.m_z, 1);

  ngl::Vec4 new_normal_V4 = normal_old * ViewMatrix;
  /*std::cout << "NewNormal is " <<
               new_normal_V4.m_x << "," <<
               new_normal_V4.m_y << "," <<
               new_normal_V4.m_z << "," <<
               new_normal_V4.m_w << std::endl;*/

  ngl::Vec3 new_normal (new_normal_V4.m_x, new_normal_V4.m_y, new_normal_V4.m_z);
  new_normal.normalize();

  //Now we compute the intersection with the new_normal
  ngl::Vec3 Ray_direction = ray.getDirection();
  float Dot_intersection = Ray_direction.dot(new_normal);
  if (Dot_intersection == 0 )
  {
    //Ray is parallel to plane
    return -1;
  }
  else
  {
    float numerator = position.dot(new_normal)-ray.getOrigin().dot(new_normal);
    return ((float)numerator/(float)Dot_intersection) - 0.00005;
  }
}
