#ifndef __CAMERA_H
#define __CAMERA_H
#include "ngl/Vec3.h"

class Camera
{
	private:
    ngl::Vec3 camPosition;
    ngl::Vec3 camLookAt;
    ngl::Vec3 camUp;
    float FOV;
		
	public:
		//Constructor and Destructor
		Camera();
    Camera(ngl::Vec3 camPosition, ngl::Vec3 camLookAt, ngl::Vec3 camUp, float FOV);
		~Camera();
		
		//Getter function
    ngl::Vec3 getcamPosition();
    ngl::Vec3 getcamLookAt();
    ngl::Vec3 getcamUp();
    ngl::Vec3 getcamDirection();
    ngl::Vec3 getcamRight();
    ngl::Vec3 getcamTrueUp();
    float getFOV();
		
		//Setter function
    void setcamPosition(ngl::Vec3 camPosition);
    void setcamLookAt(ngl::Vec3 camLookAt);
    void setcamUp(ngl::Vec3 camUp);
    void setFOV(float FOV);
};

#endif
