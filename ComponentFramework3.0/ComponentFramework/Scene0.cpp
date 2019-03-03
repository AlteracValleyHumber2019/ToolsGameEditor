#include <GL/glew.h>
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model0.h"
#include "Trackball.h"


using namespace GAME;
using namespace MATH;

Scene0::Scene0(class Window& windowRef):  Scene(windowRef), model0(nullptr) { 
	trackball = new Trackball();
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Scene0::~Scene0(){ 
	OnDestroy();
}

bool Scene0::OnCreate() {
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	/*lightPos = Vec3(10.0f, 3.0f, 10.0f);
	model0 = new Model0();
	model0->SetVel(Vec3(0.0f,0.0f,0.0f));
	model0->SetPos(Vec3(0.0f,0.0f,0.0f));*/

	gameobject = new GameObject("chair.obj");
	gameobject->SetVel(Vec3(0.0f, 0.0f, 0.0f));
	gameobject->SetPos(Vec3(0.0f, 0.0f, 0.0f));
	sceneCamera = new Camera();
	return true;
}


void Scene0::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());

	//float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	//
	//projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);

	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), 
							   Vec3(0.0f, 0.0f, 0.0f), 
							   Vec3(0.0f, 1.0f, 0.0f));
	
}

void Scene0::OnDestroy(){
	/// Cleanup Assets
	if(gameobject) delete gameobject;
	gameobject = nullptr;
	if(trackball) delete trackball;
	trackball = nullptr;
}

void Scene0::Update(const float deltaTime){
	//model0->Update(deltaTime);	
}

void Scene0::Render() const{

	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());

	Matrix4 projectionMatrix = MMath::perspective(sceneCamera->GetZoom(), aspect, 0.1f, 100.0f);
	//Matrix4 viewMatrix = sceneCamera->GetViewMatrix();

	/// Draw your scene here
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	gameobject->SetLightPos(viewMatrix * lightPos);
	gameobject->Render(projectionMatrix , trackball->GetMatrix4() *  viewMatrix, trackball->GetMatrix3());
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	/*if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN){
		trackball->OnLeftMouseDown(SDLEvent.button.x,SDLEvent.button.y);
	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION && 
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		trackball->OnMouseMove(SDLEvent.button.x,SDLEvent.button.y);
	}
	*/

	gameobject->HandleEvents(SDLEvent);
}

void Scene0::processInput(const SDL_Event &SDLEvent, float deltaTime)
{
	switch (SDLEvent.key.keysym.sym) {

	case SDLK_w:
		sceneCamera->ProcessKeyboard(CAMERA::FORWARD, deltaTime);
		printf("Move FORWARD");
		break;

	case SDLK_s:
		sceneCamera->ProcessKeyboard(CAMERA::BACKWARD, deltaTime);
		printf("Move BACKWARD");
		break;
	case SDLK_a:
		sceneCamera->ProcessKeyboard(CAMERA::LEFT, deltaTime);
		printf("Move left");
		break;

	case SDLK_d:
		sceneCamera->ProcessKeyboard(CAMERA::RIGHT, deltaTime);
		printf("Move RIGHT");
			break;
	}
}
