#include "GCamera.h"

using namespace GAME;


GCamera::GCamera(const int viewportWidth, const int viewportHeight, const Vec3 pos_)
{
	//Camera Parts
	pos = pos_; //Starting-> Current Position
	Opos = pos_; //Starting
	orientation = Vec3(0.0f, 0.0f, 10.0f);
	UpDir = Vec3(0.0f, 1.0f, 0.0f);
	aspect = float(viewportWidth) / float(viewportHeight);
	MMath::perspective(90.0f, aspect, 1.0f, 150.0f);//Perspective of the camera
	UpdateViewMatrix();
}
//Camera Components
GCamera::~GCamera()
{
}

void GCamera::UpdateViewMatrix()
{
	viewMatrix = MMath::lookAt(pos, pos + orientation, UpDir); //Matrix that controls the camera

}

void GCamera::setOrientation(const Vec3& orientation_) {

	orientation = orientation_;
	UpdateViewMatrix();
}

void GCamera::setPos(const Vec3& pos_)
{
	pos = pos_;
	UpdateViewMatrix();
}

void GCamera::setUpDir(const Vec3& dir_)
{
	UpDir = dir_;
	UpdateViewMatrix();
}

Matrix4&  GCamera::getProjectionMatrix()
{
	return projectionMatrix;
}
Matrix4&  GCamera::getViewMatrix()
{
	return viewMatrix;
}


//Movement Keys for the Camera
//____________________________________________________________
void GCamera::OnUpArrowKeyDown()
{
	setPos(Vec3(pos.x, pos.y, (pos.z + 5)));

}


void GCamera::OnDownArrowKeyDown()
{
	setPos(Vec3(pos.x, pos.y, (pos.z - 5)));
	
}

void GCamera::OnSpaceKeyDown()
{
	setPos(Vec3(pos.x, (pos.y + 2.5), pos.z));
	
}

void GCamera::OnShiftKeyDown()
{
	setPos(Vec3(pos.x, (pos.y - 2.5), pos.z));
	
}

void GCamera::OnLeftArrowKeyDown()
{
	
	setPos(Vec3((pos.x + 2.5), pos.y, pos.z));

}


void GCamera::OnRightArrowKeyDown()
{
	setPos(Vec3((pos.x - 2.5), pos.y, pos.z));

}


//Orientation of the camera

/* void GCamera::OnWKeyDown() //Y-AXIS 
{

	setOrientation(Vec3(orientation.x, (orientation.y + 3), orientation.z));
}
void GCamera::OnSKeyDown() //Y-AXIS 
{
	setOrientation(Vec3(orientation.x, (orientation.y - 3), orientation.z));
}*/

void GCamera::OnAKeyDown()//X-AXIS
{
	setOrientation(Vec3((orientation.x + 3), orientation.y, orientation.z ));
}

void GCamera::OnDKeyDown()//X-AXIS
{
	setOrientation(Vec3((orientation.x - 3), orientation.y, orientation.z));
}

void GCamera::OnRKeyDown()//X-AXIS
{

	
}
