#include <GL/glew.h>
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model0.h"
#include "Trackball.h"
#include "Collider.h"
#include "Body.h"

using namespace GAME;
using namespace MATH;

Scene0::Scene0(class Window& windowRef):  Scene(windowRef), model0(nullptr) { 
	trackball = new Trackball();
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	models = std::vector<Model*>();
}

Scene0::~Scene0(){ 
	OnDestroy();
}


//creatwes the object shader 
bool Scene0::OnCreate() {
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	lightPos = Vec3(10.0f, 3.0f, 10.0f);
	//model0 = new Model0();
	//model0->SetVel(Vec3(0.0f,0.0f,0.0f));
	//model0->SetPos(Vec3(0.0f,0.0f,0.0f));
	//Makes Obj
//	prim = new Body("triangle.obj");
	//prim2 = new Body("triangle2.obj");


	Primitive* p1 = new Primitive("cube.obj");
	prim = p1->GetBody();

	Primitive* p2 = new Primitive("cube.obj");
	prim2 = p2->GetBody();

	models.push_back(p1);
	models.push_back(p2);
	p1->SetMass(4.0f);
	p2->SetMass(8.0f);
	p1->SetRotationalInertia(4.0f);

	// rotate 
	p1->SetAngleVel(20.0);
	
	p2->SetRotationalInertia(2.0f);
	p1->SetVel(Vec3 (-1.0,0.0, 0.0));
	p2->SetVel(Vec3 (1.0,0.0,0.0 ));

	models[1]->SetPos(Vec3(0.0f, 0.0f, 2.0f));
	
	models[0]->SetPos(Vec3(0.0f, 0.0f, 2.0f));





	return true;
}


void Scene0::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	
	projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);

	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), 
							   Vec3(0.0f, 0.0f, 0.0f), 
							   Vec3(0.0f, 1.0f, 0.0f));
	
}

void Scene0::OnDestroy(){
	/// Cleanup Assets
	if(model0) delete model0;
	model0 = nullptr;
	if(trackball) delete trackball;
	trackball = nullptr;
	////deletes prim
	//if (prim) 
	//{
	//	delete prim;
	//}
	//prim = nullptr;

	////deletes prim2
	//if (prim2)
	//{
	//	delete prim2;
	//}
	//prim2 = nullptr;


	if ( models.size()>0)
	{
		for (auto m : models)
		{
			if (m)
			{
				delete m;
			}
			m = nullptr;
		}
		models.clear();
		models.shrink_to_fit();
	}
}

void Scene0::Update(const float deltaTime){
	//model0->Update(deltaTime);
	//Update obj overtime 

	//for (int i = 0; i < models.size(); i++)
	//{
	//	for (int j = i+1; j < models.size(); j++)
	//	{
	//		//Collider::HandleCollision(*models[i]->GetBody(), *models[j]->GetBody());
	//	}
	//}



	for (int i = 0; i < models.size(); i++)
	{
		
		models[i]->Update(deltaTime);
	}

	prim->Update(deltaTime);
	prim2->Update(deltaTime);



////	Checks to see is the triangles are Collieding or not
//	if (Collider::Collided(* prim,*prim2 ))
//	{	
//		std::cout << "triangles have collied" << std::endl;
//		Collider::HandleNormal(*prim, *prim2);
//	}
//	else 
//	{
//		std::cout << "triangles have  not collied" << std::endl; 
//	}
	


	
	
	
	
	
	
	
}

void Scene0::Render() const{
	/// Draw your scene here
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//model0->SetLightPos(viewMatrix * lightPos);
	//model0->Render(projectionMatrix , trackball->GetMatrix4() *  viewMatrix, trackball->GetMatrix3());
	//prim->Render(projectionMatrix, trackball->GetMatrix4() *  viewMatrix, trackball->GetMatrix3());
	//prim2->Render(projectionMatrix, trackball->GetMatrix4() *  viewMatrix, trackball->GetMatrix3());

	for (int i = 0; i < models.size();i++) 
	{
		models[i]->Render(projectionMatrix, trackball->GetMatrix4()* viewMatrix, trackball->GetMatrix3());
	}


	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	//if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN){
	//	trackball->OnLeftMouseDown(SDLEvent.button.x,SDLEvent.button.y);
	//}
	//if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION && 
	//	SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
	//	trackball->OnMouseMove(SDLEvent.button.x,SDLEvent.button.y);
	//}
	//
			
}