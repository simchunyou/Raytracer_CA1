#ifndef __MATERIAL_H
#define __MATERIAL_H
#include <ngl/Colour.h>

class Material
{
  private:
    ngl::Colour colour;
    float reflectivity;
    int specular;
    float refraction;
    float refractiveIndex;


  public:
    //Constructor and Destructor
    Material();
    Material(ngl::Colour colour, float reflectivity, float specular, float refractivity, float refractiveIndex);
    ~Material();

    //Getter function
    ngl::Colour getColour();
    float getReflectivity();
    int getSpecular();
    float getRefractivity();
    float getRefractiveIndex();

    //Setter function
    void setColour(ngl::Colour colour);
    void setReflectivity(float reflectivity);
    void setSpecular(int specular);
    void setRefractivity(float refractivity);
    void setRefractiveIndex(float refractiveIndex);
};

#endif
