#include <iostream>
#include "Renderer.h"
#include <QImage>
#include <QColor>
#include <ngl/Mat4.h>
#include <cmath>
#include "Ray.h"
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <vector>
#include <ngl/Mat4.h>
#include <ngl/Camera.h>
#include <ngl/Transformation.h>
#include <string>
#include <QString>
#include <ngl/NGLStream.h>

//Private functions
int Renderer::index_winning_intersection(std::vector <float> intersections)
{
  int index_minimum = -1;
  int value_minimum = -1;

  //if no intersections
  if (intersections.size() == 0)
  {
    return -1;
  }

  //if there is intersections
  for (int i = 0; i < (int)intersections.size(); i++)
  {
    if (intersections.at(i)<(0))
    {
      continue;
    }

    else if (index_minimum == -1)
    {
      //index_minimum is not updated
      index_minimum = i;
      value_minimum = intersections.at(i);
      continue;
    }

    else if (intersections.at(i)<value_minimum)
    {
      //If there is a smaller value, update index_minimum
      index_minimum = i;
      value_minimum = intersections.at(i);
    }
  }

  return index_minimum;
}

ngl::Vec3 Renderer::multVecMatrix(const ngl::Vec3 &src, const ngl::Mat4 &MVP)
{
  float a,b,c,w;

  a = (float)((src.m_x * MVP.m_00) + (src.m_y * MVP.m_10)  + (src.m_z * MVP.m_20) + MVP.m_30);
  b = (float)((src.m_x * MVP.m_01) + (src.m_y * MVP.m_11)  + (src.m_z * MVP.m_21) + MVP.m_31);
  c = (float)((src.m_x * MVP.m_02) + (src.m_y * MVP.m_12)  + (src.m_z * MVP.m_22) + MVP.m_32);
  w = (float)((src.m_x * MVP.m_03) + (src.m_y * MVP.m_13)  + (src.m_z * MVP.m_23) + MVP.m_33);

  ngl::Vec3 result ((float)a/(float)w,(float)b/(float)w,(float)c/(float)w);
  return result;
}

template <class t>
void Renderer::MVPPosition(std::vector<t *> Scene, ngl::Mat4 ViewMatrix)
{
  //Get Model matrix and moving each object to its new position
  for (int index = 0 ; index < (int)Scene.size(); index++)
  {
    //First we get the ModelMatrix * by vector, which is basically scene.at(index)->getPosition
    //Next we multiply our model position with our view matrix
    ngl::Vec4 ModelPosition (Scene.at(index)->getPosition().m_x,
                             Scene.at(index)->getPosition().m_y,
                             Scene.at(index)->getPosition().m_z,
                             1);
    ngl::Vec4 ViewPosition = ModelPosition * ViewMatrix ;


    //Now we get the values and input into the object position
    Scene.at(index)-> setPosition(ngl::Vec3(ViewPosition.m_x,
                                            ViewPosition.m_y,
                                            ViewPosition.m_z));
  }
}


///////////////////////////////////////////////////////////////////////////////
ngl::Colour Renderer::RenderPixel(Object* winning_object,
                                  int winningIndex,
                                  std::vector <Light*> light_objects,
                                  std::vector <Object*> scene_objects,
                                  ngl::Vec3 PointOfIntersection,
                                  ngl::Mat4 ViewMatrix,
                                  Ray IncidentRay,
                                  int reflectionbouncelimit,
                                  int* reflectionbouncepointer,
                                  int refractionbouncelimit,
                                  int* refractionbouncepointer,
                                  std::vector<int> *ray_in_index,
                                  std::vector<float> *ray_in_refractionIndex)
{
  ngl::Colour PixelColour = ngl::Colour(0,0,0,1);
  ngl::Vec3 WinningNormal = winning_object->getNormalAt(PointOfIntersection);
  WinningNormal.normalize();

  //Update reflection and refraction bounce
  *reflectionbouncepointer +=1;
  *refractionbouncepointer +=1;

  //Calculating reflections
  //*****************************************************************//

  if(*reflectionbouncepointer <= reflectionbouncelimit)
  {
    //Check if the ray is entering a different medium or not and if it is
    if (winning_object->getMaterial().getReflectivity() != 0) //Only if object has reflection
    {
      //Calculate reflection ray
      ngl::Vec3 Reflection_Ray_Direction = IncidentRay.getDirection() - 2*(IncidentRay.getDirection().dot(WinningNormal))*WinningNormal;
      Ray Reflection_Ray (PointOfIntersection, Reflection_Ray_Direction);

      //We create a vector to store reflection intersections
      std::vector <float> reflection_intersections;

      //We launch the reflection ray and see what it hits
      for (int i = 0; i < (int) scene_objects.size(); i++)
      {
        reflection_intersections.push_back(scene_objects.at(i)->findIntersection(Reflection_Ray,ViewMatrix,0));
      }

      //Calculate the winning object index
      int winning_reflection_index = index_winning_intersection(reflection_intersections);

      //If there is intersections
      if (winning_reflection_index != -1 && reflection_intersections.at(winning_reflection_index) > 0.0005)
      {
        float LengthOfReflectedIntersection = reflection_intersections.at(winning_reflection_index);
        //Get new reflected Point of intersection
        ngl::Vec3 ReflectedPointOfIntersection = Reflection_Ray.getOrigin()+ LengthOfReflectedIntersection*Reflection_Ray.getDirection();

        //Get the colour
        ngl::Colour getReflectedColour = RenderPixel(scene_objects.at(winning_reflection_index),
                                                     winning_reflection_index,
                                                     light_objects,
                                                     scene_objects,
                                                     ReflectedPointOfIntersection,
                                                     ViewMatrix,
                                                     Reflection_Ray,
                                                     reflection_bounce_limit,
                                                     reflectionbouncepointer,
                                                     refraction_bounce_limit,
                                                     refractionbouncepointer,
                                                     ray_in_index,
                                                     ray_in_refractionIndex);
        //Return the colour and add to reflection
        ngl::Colour ReflectedColour = getReflectedColour*winning_object->getMaterial().getReflectivity();
        PixelColour = PixelColour + ReflectedColour;
      }

    }
  }


  //Calculating refractions
  //*****************************************************************//
  if(*reflectionbouncepointer <= reflectionbouncelimit)
  {
    //Check if the object has refraction or not
    if (winning_object->getMaterial().getRefractivity() != 0) //Only if object has refraction
    {
      //Determining Incident medium and refracted medium
      float r1=ray_in_refractionIndex->back();
      if (winningIndex == ray_in_index->back()) //This means that the ray is just exiting the medium it was inside
      {
        ray_in_refractionIndex->pop_back();
        ray_in_index->pop_back();
      }
      else
      {
        ray_in_refractionIndex->push_back(winning_object->getMaterial().getRefractiveIndex());
        ray_in_index->push_back(winningIndex);
      }
      float r2 = ray_in_refractionIndex->back();

      float Snell = r1/r2;

      //Calculating refractedRayDirection
      ngl::Vec3 R_A = Snell*IncidentRay.getDirection();
      float R_B = Snell*( -1*IncidentRay.getDirection().dot(WinningNormal));
      float R_C = 1-(Snell*Snell - Snell*Snell*(-1*IncidentRay.getDirection().dot(WinningNormal)*(-1*IncidentRay.getDirection().dot(WinningNormal))));
      R_C = sqrt(R_C);
      ngl::Vec3 Refraction_Ray_Direction = R_A + (R_B - R_C)*WinningNormal;
      Refraction_Ray_Direction.normalize();

      Ray Refraction_Ray (PointOfIntersection, Refraction_Ray_Direction);

      //We create a vector to store refraction intersections
      std::vector <float> refraction_intersections;

      //We launch the refracted ray and see what it hits
      for (int i = 0; i < (int) scene_objects.size(); i++)
      {
        bool reverse = 0;
        if (scene_objects.at(i) == winning_object)
        {
          //This means that the ray is produced inside the object and reaches the other side of the object
          //In this case, the normals is reverse when calculating intersections
          reverse = 1;
        }
        refraction_intersections.push_back(scene_objects.at(i)->findIntersection(Refraction_Ray,ViewMatrix,reverse));
      }

      //Calculate the winning object index
      int winning_refraction_index = index_winning_intersection(refraction_intersections);

      //If there is intersections
      if (winning_refraction_index != -1 && refraction_intersections.at(winning_refraction_index) > 0.0005)
      {
        float LengthOfRefractedIntersection = refraction_intersections.at(winning_refraction_index);
        //Get new refracted Point of intersection
        ngl::Vec3 RefractedPointOfIntersection = Refraction_Ray.getOrigin()+ LengthOfRefractedIntersection*Refraction_Ray.getDirection();

        //Get the colour
        ngl::Colour getRefractedColour = RenderPixel(scene_objects.at(winning_refraction_index),
                                                     winning_refraction_index,
                                                     light_objects,
                                                     scene_objects,
                                                     RefractedPointOfIntersection,
                                                     ViewMatrix,
                                                     Refraction_Ray,
                                                     reflection_bounce_limit,
                                                     reflectionbouncepointer,
                                                     refraction_bounce_limit,
                                                     refractionbouncepointer,
                                                     ray_in_index,
                                                     ray_in_refractionIndex);
        //Return the colour and add to refraction
        ngl::Colour RefractionColour = getRefractedColour*winning_object->getMaterial().getRefractivity();
        PixelColour = PixelColour + RefractionColour;
      }

    }
  }



  //Calculating shadows
  //*****************************************************************//
  //Loop through light sources and see if shadow ray hits light or not
  for (int i = 0; i< (int)light_objects.size(); i++)
  {
    //Shadowed is currently false
    bool shadowed = false;

    //Calculate direction of shadow_ray
    ngl::Vec3 Shadow_Ray_Direction = light_objects.at(i)->getPosition() - PointOfIntersection;

    //Calculate distance form object to light&ray_in_index,
    float LightDistance = Shadow_Ray_Direction.length();

    //Normalize shadow_ray
    Shadow_Ray_Direction.normalize();

    //Calculate dot product from light to normal
    float cosine_angle = WinningNormal.dot(Shadow_Ray_Direction);

    if(cosine_angle > 0)
    {
      //Create shadow ray
      Ray Shadow_Ray(PointOfIntersection, Shadow_Ray_Direction);

      //Create a vector to store secondary intersections.
      std::vector <float> secondary_intersections;

      //Calculate secondary intersections
      for (int index = 0 ; index < (int)scene_objects.size(); index++)
      {
        secondary_intersections.push_back(scene_objects.at(index)->findIntersection(Shadow_Ray, ViewMatrix,0));
      }

      //Check if shadowed
      for (int i = 0; i < (int)secondary_intersections.size(); i++)
      {
        if (secondary_intersections.at(i) > 0.00005 && secondary_intersections.at(i) < LightDistance) //Calculation errors
        {
          shadowed = true;
        }
      }

      //Not in shadow
      if (shadowed == false)
      {
        ngl::Colour Lighting = (winning_object->getMaterial().getColour()*light_objects.at(i)->getColour()*light_objects.at(i)->getIntensity())*cosine_angle;
        PixelColour = PixelColour + Lighting*(1-winning_object->getMaterial().getRefractivity());

        //if object is reflective
        if (winning_object->getMaterial().getSpecular()>0) //Only if object has specular
        {
          //Calculate reflection ray direction
          ngl::Vec3 Reflection_Ray_Direction = IncidentRay.getDirection() - 2*(IncidentRay.getDirection().dot(WinningNormal))*WinningNormal;

          //Calculate specular
          float specular = Reflection_Ray_Direction.dot(Shadow_Ray_Direction);
          if (specular>0)
          {
            specular = pow(specular,(int)winning_object->getMaterial().getSpecular());
            PixelColour = PixelColour + (light_objects.at(i)->getColour()*(specular*winning_object->getMaterial().getReflectivity()));
          }
        }

      }
    }

  }
  //*****************************************************************//

  //PixelColour clamping
  if (PixelColour.m_r > 1)
  {
    PixelColour.m_r = 1;
  }

  if (PixelColour.m_g > 1)
  {
    PixelColour.m_g = 1;
  }

  if (PixelColour.m_b > 1)
  {
    PixelColour.m_b = 1;
  }

  return PixelColour;
}
///////////////////////////////////////////////////////////////////////////////
//Constructor and Destructor
Renderer::Renderer()
{
  //Default Values
  imageHeight = 1280;
  imageWidth = 720;
  saveimage = 0;
  saveimagename = "untitled.jpg";
}

Renderer::~Renderer()
{
  //std::cout << "Renderer has been deleted" << std::endl;
}

//Getter Functions
int Renderer::getHeight()
{
  return imageHeight;
}

int Renderer::getWidth()
{
  return imageWidth;
}
float Renderer::getAspectRatio()
{
  return (float)imageWidth/(float)imageHeight;
}

int Renderer::getReflectionBounce()
{
  return reflection_bounce_limit;
}

int Renderer::getRefractionBounce()
{
  return refraction_bounce_limit;
}

bool Renderer::getsaveimage()
{
  return saveimage;
}

//Setter Functions
void Renderer::setHeight(int height)
{
  imageHeight = height;
}

void Renderer::setWidth(int width)
{
  imageWidth = width;
}

void Renderer::setReflectionBounce(int ReflectionBounce)
{
  reflection_bounce_limit = ReflectionBounce;
}

void Renderer::setRefractionBounce(int RefractionBounce)
{
  refraction_bounce_limit = RefractionBounce;
}

void Renderer::setSaveImage(bool saveimage)
{
  this -> saveimage = saveimage;
  saveimagename = "untitled.jpg";
}

void Renderer::setSaveImage(bool saveimage, std::string saveimagename)
{
  this -> saveimage = saveimage;
  this -> saveimagename = saveimagename;

}

void Renderer::setSceneCamera(ngl::Camera* camera)
{
  this -> camera = camera;
}

void Renderer::setSceneScene(Scene* scene)
{
  this -> scene = scene;
}

//Method Functions
void Renderer::render()
{
  //Create a QImage for saving
  image = QImage(imageWidth,imageHeight,QImage::Format_RGB32);

  //Unloading the Object and Light vectors and creating a copy
  std::vector <Object*> Scene_Objects = scene->getSceneObjects();
  std::vector <Light*> Light_Objects = scene->getLightObjects();

  //Setting some variables for camera ray calculation
  float fov = camera->getFOV();
  float AspectRatio = (float)imageWidth/(float)imageHeight;

  //To convert degrees to radians, you do
  // deg * M_PI /180.0 with cmath library included.
  float scale = (tan(fov*0.5*M_PI/180));

  //Get View matrix
  ngl::Mat4 ViewMatrix = camera->getViewMatrix();

  //Storing model and light position for re-render
  std::vector <ngl::Vec3> ModelOriginal;
  std::vector <ngl::Vec3> LightOriginal;
  for (int index = 0 ; index < (int)Scene_Objects.size(); index++)
  {
    ModelOriginal.push_back(Scene_Objects.at(index)->getPosition());
  }
  for (int index = 0 ; index < (int)Light_Objects.size(); index++)
  {
    LightOriginal.push_back(Light_Objects.at(index)->getPosition());
  }

  //Moving objects with MVP
  MVPPosition(Scene_Objects, ViewMatrix);
  MVPPosition(Light_Objects, ViewMatrix);

  //Calculating intersection and generating values
  for (int i = 0; i <imageWidth; i++)
  {
    for (int j=0; j<imageHeight; j++)
    {
      //Create values for reflection and refraction depth
      int reflection_bounce = 0;
      int* reflection_bounce_pointer = &reflection_bounce;
      int refraction_bounce = 0;
      int* refraction_bounce_pointer = &refraction_bounce;

      //Creating a ray to shoot through middle of pixel in screen space
      float x,y;
      x = (2*(i+0.5)/(float)imageWidth -1)*scale;
      y = (1-2*(j+0.5)/(float)imageHeight)*scale*1/AspectRatio;

      ngl::Vec3 cam_ray_origin (0,0,0);
      ngl::Vec3 cam_ray_direction = ngl::Vec3(x,y,-1);
      cam_ray_direction.normalize();

      //Create the ray
      Ray cam_ray(cam_ray_origin,cam_ray_direction);

      //create a vector of intersections and compare which is the closest
      std::vector <float> intersections;

      for (int index = 0 ; index < (int)Scene_Objects.size(); index++)
      {
        intersections.push_back(Scene_Objects.at(index)->findIntersection(cam_ray, ViewMatrix,0));
      }

      //Calculate the winning object index
      int winning_index = index_winning_intersection(intersections);
      //Get colour at pixel
      //If there is no intersections
      if (winning_index == -1)
      {
        image.setPixel(i,j,qRgb(0,0,0));
      }

      //If there is intersections
      else
      {
        //To keep track of refraction medium
        std::vector<int> ray_in_index;
        ray_in_index.push_back(-99);
        std::vector<float> ray_in_refraction;
        ray_in_refraction.push_back(1);

        float LengthOfIntersection = intersections.at(winning_index);
        ngl::Vec3 PointOfIntersection = cam_ray.getOrigin()+LengthOfIntersection*cam_ray.getDirection();
        ngl::Colour getColour = RenderPixel(Scene_Objects.at(winning_index),
                                            winning_index,
                                            Light_Objects,
                                            Scene_Objects,
                                            PointOfIntersection,
                                            ViewMatrix,
                                            cam_ray,
                                            reflection_bounce_limit,
                                            reflection_bounce_pointer,
                                            refraction_bounce_limit,
                                            refraction_bounce_pointer,
                                            &ray_in_index,
                                            &ray_in_refraction);
        float Colour_R = getColour.m_r * 255;
        float Colour_G = getColour.m_g * 255;
        float Colour_B = getColour.m_b * 255;
        image.setPixel(i,j,qRgb(Colour_R,Colour_G,Colour_B));
      }
    }
  }

  //Resetting the model and lights position for rerender
  for (int index = 0 ; index < (int)Scene_Objects.size(); index++)
  {
    Scene_Objects.at(index)->setPosition(ModelOriginal.at(index));
  }
  for (int index = 0 ; index < (int)Light_Objects.size(); index++)
  {
    Light_Objects.at(index)->setPosition(LightOriginal.at(index));
  }
  std::cout << "Rendered" << std::endl;

  if (saveimage == 1)
  {
    QString qsaveimagename = QString::fromStdString(saveimagename);
    image.save(qsaveimagename,0,100);
  }

}
