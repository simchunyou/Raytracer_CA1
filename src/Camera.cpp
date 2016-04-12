#include <iostream>
#include "Camera.h"
#include "ngl/Vec3.h"

//Constructor and Destructor
Camera::Camera()
{
  camPosition = ngl::Vec3(0,0,0);
  camLookAt = ngl::Vec3(0,0,-1);
  camUp = ngl::Vec3(0,1,0);
  FOV = 90;
}

Camera::Camera(ngl::Vec3 camPosition, ngl::Vec3 camLookAt, ngl::Vec3 camUp, float FOV)
{
	this -> camPosition = camPosition;
	this -> camLookAt = camLookAt;
	this -> camUp = camUp;
  this -> FOV = FOV;
}

Camera::~Camera()
{
	//std::cout << "Camera has been deleted" << std::endl;
}

//Getter function
ngl::Vec3 Camera::getcamPosition()
{
	return camPosition;
}
ngl::Vec3 Camera::getcamLookAt()
{
	return camLookAt;
}
ngl::Vec3 Camera::getcamUp()
{
	return camUp;
}
ngl::Vec3 Camera::getcamDirection()
{
  ngl::Vec3 camDirection = camLookAt + camPosition*(-1);
  camDirection.normalize();
  return camDirection;
}
ngl::Vec3 Camera::getcamRight()
{
  ngl::Vec3 camDirection = camLookAt + camPosition*(-1);
  camDirection.normalize();
  ngl::Vec3 camRight = camUp.cross(camDirection);
  camRight.normalize();
  return camRight;
}
ngl::Vec3 Camera::getcamTrueUp()
{
  ngl::Vec3 camDirection = camLookAt + camPosition*(-1);
  camDirection.normalize();
  ngl::Vec3 camRight = camUp.cross(camDirection);
  camRight.normalize();
  ngl::Vec3 camTrueUp = camRight.cross(camDirection);
  return camTrueUp;
}

float Camera::getFOV()
{
  return FOV;
}

//Setter function
void Camera::setcamPosition(ngl::Vec3 camPosition)
{
	this -> camPosition = camPosition;
}
void Camera::setcamLookAt(ngl::Vec3 camLookAt)
{
	this -> camLookAt = camLookAt;
}
void Camera::setcamUp(ngl::Vec3 camUp)
{
	this -> camUp = camUp;
}
void Camera::setFOV(float FOV)
{
  this -> FOV = FOV;
}
