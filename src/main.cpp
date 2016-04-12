/****************************************************************************
basic OpenGL demo modified from http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
****************************************************************************/
//http://mycodelog.com/tag/gldrawpixels/
//http://stackoverflow.com/questions/20056174/gldrawpixel-rgb-value-from-a-array
//http://www.cs.mun.ca/~blangdon/opengl/glDrawPixels.html
//https://open.gl/textures

#include <QtGui/QGuiApplication>
#include <QApplication>
#include <iostream>
#include "NGLScene.h"

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <vector>
#include <ngl/Camera.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>

#include "Renderer.h"
#include "Light.h"
#include "Ray.h"
#include "Material.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Scene.h"

#include "mainwindow.h"
int main(int argc, char **argv)
{
  //Setting up the scene
  Scene CYscene;

  //Setting up the renderer
  Renderer CYrenderer;
  CYrenderer.setWidth(1024);
  CYrenderer.setHeight(720);
  CYrenderer.setReflectionBounce(4);
  CYrenderer.setRefractionBounce(4);
  CYrenderer.setSaveImage(0,"test1.jpg");

  //Setting up the camera
  ngl::Camera JMcamera;
  JMcamera.set(ngl::Vec3(0,3,20),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0));
  JMcamera.setShape(60.0f,((float)CYrenderer.getWidth()/(float)CYrenderer.getHeight()),0.1f,100.0f);

  //Setting up the lights
  Light CYlight(ngl::Vec3(-7,10,10),ngl::Colour(1,1,1,1),1.0f);
  Light CYlight2(ngl::Vec3(7,10,-10),ngl::Colour(1,1,1,1),2.0f);

  //Create materials
  Material red;
  red.setColour(ngl::Colour(0.8,0.2,0.2,1));
  red.setReflectivity(0.4);
  red.setSpecular(5);

  Material blue;
  blue.setColour(ngl::Colour(0.2,0.2,0.8,1));

  Material green;
  green.setColour(ngl::Colour(0.2,0.9,0.1,1));
  green.setRefractivity(0.7);
  green.setRefractiveIndex(1.3);

  //Set up the scene
  Sphere CYsphere(ngl::Vec3 (0,2.5,-5), 2.5);
  CYsphere.assignMaterial(red);
  Sphere CYsphere2(ngl::Vec3 (0,1,5), 1);
  CYsphere2.assignMaterial(green);
  Plane CYplane (ngl::Vec3 (0,0,0), ngl::Vec3(0,1,0));
  CYplane.assignMaterial(blue);

  //Assigning objects to the scene
  CYscene.addSceneObjects(&CYsphere);
  CYscene.addSceneObjects(&CYsphere2);
  CYscene.addSceneObjects(&CYplane);
  CYscene.addLightObjects(&CYlight);
  CYscene.addLightObjects(&CYlight2);


  //Setting render camera and scene
  CYrenderer.setSceneCamera(&JMcamera);
  CYrenderer.setSceneScene(&CYscene);

  //Render out the scene
  CYrenderer.render();

  /***********************************************************************************
   * ********************************************************************************/
  /*
   * Setting Up the window and initializing and running
   * */

  QApplication app(argc, argv);
  // create an OpenGL format specifier
  QSurfaceFormat format;
  // set the number of samples for multisampling
  // will need to enable glEnable(GL_MULTISAMPLE); once we have a context
  format.setSamples(4);
  #if defined( __APPLE__)
    // at present mac osx Mountain Lion only supports GL3.2
    // the new mavericks will have GL 4.x so can change
    format.setMajorVersion(4);
    format.setMinorVersion(1);
  #else
    // with luck we have the latest GL version so set to this
    format.setMajorVersion(4);
    format.setMinorVersion(3);
  #endif
  // now we are going to set to CoreProfile OpenGL so we can't use and old Immediate mode GL
  format.setProfile(QSurfaceFormat::CoreProfile);
  // now set the depth buffer to 24 bits
  format.setDepthBufferSize(24);

  QSurfaceFormat::setDefaultFormat(format);

/*
  // now we are going to create our scene window
  //NGLScene window(&CYrenderer);
  NGLScene window;
  // and set the OpenGL format
  window.setFormat(format);
  // we can now query the version to see if it worked
  std::cout<<"Profile is "<<format.majorVersion()<<" "<<format.minorVersion()<<"\n";
  // set the window size
  window.resize(1024, 720);
*/
  /***********************************************************************************
   * ********************************************************************************/

  MainWindow w(&CYrenderer);
  w.show();

  // and finally show
  //window.show();

  return app.exec();
}



