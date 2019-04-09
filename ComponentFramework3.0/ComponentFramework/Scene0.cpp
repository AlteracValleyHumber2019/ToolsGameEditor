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
	//OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	/*lightPos = Vec3(10.0f, 3.0f, 10.0f);
	model0 = new Model0();
	model0->SetVel(Vec3(0.0f,0.0f,0.0f));
	model0->SetPos(Vec3(0.0f,0.0f,0.0f));*/

	//SDL_ShowCursor(SDL_DISABLE);
	firstMouse = true;

	gameobjects.push_back(new GameObject("chair.obj", Vec3(0, 0, 0)));
	gameobjects.push_back(new GameObject("cube.obj", Vec3(0, 5, 0)));


	sceneCamera = new Camera(Vec3(0,0,5));

	lastX = windowPtr->GetWidth() / 2;
	lastY = windowPtr->GetHeight() / 2;
	return true;
}


void Scene0::OnResize(int w_, int h_){
	//windowPtr->SetWindowSize(w_,h_);
	//glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());

	//float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	//
	//projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);

	/*viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), 
							   Vec3(0.0f, 0.0f, 0.0f), 
							   Vec3(0.0f, 1.0f, 0.0f));*/
	
}

void Scene0::OnDestroy(){
	/// Cleanup Assets
	for (auto object: gameobjects)
	{
		if (object) delete object;
		object = nullptr;
	}


	if(trackball) delete trackball;
	trackball = nullptr;
}

void Scene0::Update(const float deltaTime){
	//model0->Update(deltaTime);	
}

void Scene0::Render(){

	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());

	//projectionMatrix_ = MMath::perspective(sceneCamera->GetZoom(), aspect, 0.1f, 100.0f);
	//viewMatrix_ = sceneCamera->GetViewMatrix();

	/// Draw your scene here
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for (auto object : gameobjects)
	{
		object->SetLightPos(viewMatrix_ * lightPos);
		object->Render(projectionMatrix_, viewMatrix_, trackball->GetMatrix3());
	}

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::ObjectSelection()
{
	int MouseXPos, MouseYPos;
	SDL_GetMouseState(&MouseXPos, &MouseYPos);
	for (auto objects : gameobjects)
	{
		if(objects->CheckCollisonSelection(MouseXPos, MouseYPos))
		{
			objects->ObjectSelected = true;
		}else
		{
			objects->ObjectSelected = false;
		}
	}
}
void Scene0::HandleEvents(const SDL_Event& SDLEvent){

	for (auto object : gameobjects)
	{
		object->HandleEvents(SDLEvent);
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		ObjectSelection();
		printf("Object Selected");
	}
}

void Scene0::placeObjects(char*object_)
{
	// get the mouse x and y pos
	int MouseXPos, MouseYPos;
	SDL_GetMouseState(&MouseXPos, &MouseYPos);

	Vec3 ObjectLoc = getObjectLocation(MouseXPos, MouseYPos);

	gameobjects.push_back(new GameObject(object_, ObjectLoc));
}
Vec3 Scene0::getObjectLocation(float mouseX, float mouseY)
{
	Matrix4 matProjectionInvers = MMath::inverse(viewMatrix_ * projectionMatrix_);
	Vec4 vIn;
	float winZ = 1.0;

	vIn.x = (2.0f*((float)(mouseX - 0) / ((float)windowPtr->GetWidth() - 0))) - 1.0f;
	vIn.y = 1.0f - (2.0f*((float)(mouseY - 0) / ((float)windowPtr->GetHeight() - 0)));
	vIn.z = 2.0 * winZ - 1.0;
	vIn.w = 1.0f;

	vIn = matProjectionInvers * vIn;
	vIn.w = 1.0 / vIn.w;

	vIn.x *= vIn.w;
	vIn.y *= vIn.w;
	vIn.z *= vIn.w;

	return  Vec3(vIn.x, vIn.y, vIn.z);
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
	case SDLK_l:
		placeObjects("chair.obj");
		printf("Place Object");
		break;
	}
}

void Scene0::processMouseInput(const SDL_Event &SDLEvent)
{
	int _xPos, _yPos;
	if (SDLEvent.type == SDL_MOUSEMOTION && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		
		SDL_GetMouseState(&_xPos, &_yPos);

		//camera mouse movement
		if (firstMouse)
		{
			lastX = _xPos;
			lastY = _yPos;
			firstMouse = false;
		}

		float xoffset = _xPos - lastX;
		float yoffset = lastY - _yPos; // reversed since y-coordinates go from bottom to top

		lastX = _xPos;
		lastY = _yPos;

		sceneCamera->ProcessMouseMovement(xoffset, yoffset);

	}
}
