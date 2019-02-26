#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Body.h"


using namespace MATH;

class Scene;


namespace GAME {

class Model {
protected:

	
	
	Body* body;
	Sphere bounding;
	Matrix4 modelMatrix;
	Scene* parentScene;
	std::vector<Mesh*> meshes;

public:


	inline void SetPos(const Vec3& pos_)
	{ 
		if (body) 
		{
			body->SetPosition(pos_);
		}
		
	}

	inline void SetMass(const float& mass_)
	{
		if (body)
		{
			body->setMass(mass_);
		}

	}

	inline void SetRotationalInertia(const float& RotationalInertia_)
	{
		if (body)
		{
			body->setRotationalInertia(RotationalInertia_);
		}

	}



	inline void SetVel(const Vec3& vel_){
		if (body)
		{
			body->SetVelocity(vel_);
		}
	}



	inline void SetAngleVel(const float& anglevel_)
	{
		if (body)
		{
			body->SetAngularVel(anglevel_);
		}

	}

	inline Body* GetBody() 
	{
		return body;
	
	}

	virtual ~Model()
	{
		if (body) 
		{
			delete body;
		}
		body = nullptr;
	
	};



	Model(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator = (const Model&) = delete;
	Model& operator = (Model&&) = delete;
	Model() {};
//	Model() : gravity(0.0f,-9.8f,0.0f)  { };
 

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix)const = 0;


virtual	void Update(const float deltaTime){
		//pos += vel * deltaTime + 0.5f * gravity * deltaTime * deltaTime;
		//vel += gravity * deltaTime;
		if (body) 
		{
			body->Update(deltaTime);
		}
	}


};




} /// end of namespace

#endif