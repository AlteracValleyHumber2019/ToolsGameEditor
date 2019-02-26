#ifndef  BODY_H
#define BODY_H
#include "Vector.h"
#include <vector>
using namespace MATH;

class Body
{
public:

	Vec3 getPos()const;

	float getMass()const;
	Vec3 getVel()const;
	Vec3 getAccel()const;
	Vec3 getWorld()const;

	float getRotationalInertia()const;
	float getAngle()const;
	float getAngularVel()const;
	float getAngularAcc()const;
	std::vector<Vec3> GetShape()const;

	void SetPosition(Vec3 pos_);
	void setRotationalInertia(float RotationalInertia_);
	void setMass(float mass_);
	void SetVelocity(Vec3 vel_);
	void SetAngularVel(float angularVel_);
	void SetShape(std::vector<Vec3> shape_);
	void Update(double timestep); // Updates position, velocity, force and torque using equations of motion
	void ApplyForce(Vec3& force); // updates force
	void ApplyTorque(float torque);//updates torque
	void ApplyAngle(float timestep);
	void ApplyworldForce(Vec3& force);
	void GetShape(std::vector<Vec3> shape_);
	void AddPoint(Vec3 point_);
	// Overloaded constructor that sets all member variable to given values
	Body(double newMass, Vec3 newWorldSpace, float newangle, float newangularVel, float newangularAcc, float newrotationalInertia_, Vec3& newPosition, Vec3& newVelocity, Vec3& newAcceleration);// try double newfinalVel
	Body(double newMass, float  rotationalInertia); // The constructor. Sets the mass to the given value and everything else to [0, 0]
	
	//Body(Vec3 pos, Vec3  pos2 ,Vec3 pos3); // The constructor. Sets the mass to the given value and everything else to [0, 0]

	~Body();

private:
	double mass;
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	Vec3 World;
	float  rotationalInertia;
	float angle, angularVel, angularAcc;
	std::vector<Vec3>shape;


};

#endif   BODY_H