#include "Body.h"
#include "VMath.h"
#include "MMath.h"
#include <iostream>
using namespace std;

using namespace MATH;
Body::Body(double newMass, Vec3 newWorldSpace, float newangle, float newangularVel, float newangularAcc, float newrotationalInertia_, Vec3& newPosition, Vec3& newVelocity, Vec3& newAcceleration)
{
	mass = newMass;// mass of ship
	accel = newAcceleration;// the acceleration of the ship
	vel = newVelocity;//  velocity 
	pos = newPosition;// postion of rider
	rotationalInertia = newrotationalInertia_;// the rotation of inertia 
	angle = 0;// angle of ship
	angularAcc = 0;// angle acceleration
	angularVel = 0; //angle velocity 
	World = 0;
	shape = std::vector<Vec3>();

}

Body::Body(double newMass, float rotationalInertia)
{
}

Body::~Body()
{
	if (shape.size() > 0)
	{
		shape.clear();
		shape.shrink_to_fit();
	}
}




//equation angularAcc
void Body::ApplyTorque(float torque)
{
	//omgea = torque / Inertia;
	angularAcc = torque / rotationalInertia;


}



//Body::Body(Vec3 pos, Vec3 pos2, Vec3 pos3)
//{
//}

void Body::Update(double timestep)
{
	//updates velocity vector
	angularVel += (angularAcc * timestep);

	//updates the orientation angle 
	angle += (angularVel* timestep) + (0.5 * angularAcc) * (timestep * timestep);


	//updates the x and y veloicity of ship
	vel.x += (accel.x * timestep);
	vel.y += (accel.y * timestep);


	//update the postion of ship over time
	pos.x += (vel.x * timestep) + (0.5 * accel.x) * (timestep * timestep);
	pos.y += (vel.y * timestep) + (0.5 * accel.y) * (timestep * timestep);


}

// Updates position and velocity using equations of motion
void Body::ApplyForce(Vec3& force) {


	//rotates  the vector in a 2D Matrix
	float WorldSpacex = (force.x *(cos(angle)) - (force.y *(sin(angle))));
	float WorldSpacey = (force.y *(sin(angle)) + (force.x *(cos(angle))));
	Vec3 World = Vec3(WorldSpacex, WorldSpacey, 0.0f);



	// linear accel
	accel.x = World.x / mass;
	accel.y = World.y / mass;




}


void Body::GetShape(std::vector<Vec3> shape_)
{
	shape = shape_;
}

void Body::AddPoint(Vec3 point_)
{
	shape.push_back(point_);
}



Vec3 Body::getPos() const
{
	return pos;
}


float Body::getMass() const
{
	return mass;
}




Vec3 Body::getVel() const
{
	return vel;
}

Vec3 Body::getAccel() const
{
	return accel;
}

Vec3 Body::getWorld() const
{
	return World;
}



float Body::getRotationalInertia() const
{
	return rotationalInertia;
}

float Body::getAngle() const
{
	return angle;
}

float Body::getAngularVel() const
{
	return angularVel;
}

float Body::getAngularAcc() const
{
	return angularAcc;
}

std::vector<Vec3> Body::GetShape() const
{
	return shape;
}

void Body::SetPosition(Vec3 pos_)
{
	pos = pos_;
}

void Body::setRotationalInertia(float RotationalInertia_)
{
	rotationalInertia = RotationalInertia_;
}






void Body::setMass(float mass_)
{
	mass = mass_;
}

void Body::SetVelocity(Vec3 vel_)
{
	vel = vel_;
}

void Body::SetAngularVel(float angularVel_)
{
angularVel = angularVel_;
}

void Body::SetShape(std::vector<Vec3> shape_)
{
	shape = shape_;
}
