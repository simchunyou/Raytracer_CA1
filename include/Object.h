#ifndef __OBJECT_H
#define __OBJECT_H
#include "Material.h"
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Ray.h"

class Object
{
  private:
    Material material;

  protected:
    ngl::Vec3 position;

  public:
    //Constructor and Destructor
    Object();
    Object(Material material);
    ~Object();

    //Getter function
    Material getMaterial();
    virtual ngl::Vec3 getPosition();
    virtual ngl::Vec3 getNormalAt(ngl::Vec3 point);

    //Setter function
    void assignMaterial(Material material);
    virtual void setPosition(ngl::Vec3 p);

    //Method function
    virtual float findIntersection(Ray ray, ngl::Mat4 ViewMatrix, bool reverseNormal);
};

#endif
