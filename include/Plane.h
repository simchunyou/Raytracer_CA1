#ifndef __PLANE_H
#define __PLANE_H
#include <ngl/Vec3.h>
#include "Object.h"
#include <ngl/Mat4.h>

class Plane : public Object
{
  private:
    //ngl::Vec3 position;
    ngl::Vec3 normal;

  public:
    //Constructor and Destructor
    Plane();
    Plane(ngl::Vec3 p, ngl::Vec3 n);
    ~Plane();

    //Getter function
    ngl::Vec3 getPosition();
    ngl::Vec3 getNormalAt(ngl::Vec3 point);

    //Setter function
    void setPosition(ngl::Vec3 p);
    void setNormal(ngl::Vec3 n);

    //Method function
    float findIntersection(Ray ray, ngl::Mat4 ViewMatrix, bool reverseNormal);
};

#endif
