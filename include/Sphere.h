#ifndef __SPHERE_H
#define __SPHERE_H
#include <ngl/Vec3.h>
#include "Object.h"
#include <ngl/Mat4.h>

class Sphere : public Object
{
  private:
    //ngl::Vec3 position;
    float radius;

  public:
    //Constructor and Destructor
    Sphere();
    Sphere(ngl::Vec3 p, float r);
    ~Sphere();

    //Getter function
    ngl::Vec3 getPosition();
    float getRadius();

    //Setter function
    void setPosition(ngl::Vec3 p);
    void setRadius(float r);

    //Method function
    ngl::Vec3 getNormalAt(ngl::Vec3 point);
    float findIntersection(Ray ray, ngl::Mat4 ViewMatrix, bool reverseNormal);
};

#endif
