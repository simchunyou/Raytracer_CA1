#ifndef __RAY_H
#define __RAY_H
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>

class Ray
{
  private:
    ngl::Vec3 origin;
    ngl::Vec3 direction;
    float medium;

  public:
    //Constructor and Destructor
    Ray();
    Ray(ngl::Vec3 origin, ngl::Vec3 direction);
    Ray(ngl::Vec4 origin, ngl::Vec4 direction);
    ~Ray();

    //Getter function
    ngl::Vec3 getOrigin();
    ngl::Vec3 getDirection();
    float getMedium();

    //Setter function
    void setOrigin(ngl::Vec3 origin);
    void setDirection(ngl::Vec3 direction);
    void setMedium(float medium);

};

#endif
