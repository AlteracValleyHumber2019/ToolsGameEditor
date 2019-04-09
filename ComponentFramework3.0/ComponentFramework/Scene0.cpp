#include <GL/glew.h>
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model0.h"
#include "Trackball.h"
#include <stdio.h>

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

	SDL_ShowCursor(SDL_DISABLE);
	firstMouse = true;
	gameobject = new GameObject("chair.obj");
	gameobject->SetVel(Vec3(0.0f, 0.0f, 0.0f));
	gameobject->SetPos(Vec3(0.0f, 0.0f, 0.0f));
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
	if(gameobject) delete gameobject;
	gameobject = nullptr;
	if(trackball) delete trackball;
	trackball = nullptr;

	//Clean Up ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
}

void Scene0::Update(const float deltaTime){

	/// Declare boolean of checkbox variables
	static bool show_control_window = false;
	static bool show_another_window = false;
	static bool show_demo_window = false;

	/// 1. ImGui window opens with newFrame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(windowPtr->getSDLWindow());
	ImGui::NewFrame();
	ImGui::Begin("Editor Menu");

	/// Checkbox features will open and close Window
	ImGui::Checkbox("Control Window", &show_control_window);
	ImGui::Checkbox("Demo Window", &show_demo_window);
	ImGui::Checkbox("Object Manager", &show_another_window);

	// 1. This is control menu where you can move rotate object and camera 
	if (show_control_window) {
		if (!ImGui::Begin("Control Window", &show_control_window))
		{
			ImGui::End();
		}
		else {
			// 2. Camera feature up, down, left, right
			ImGui::Text("1: Viewport Camera");
			ImGui::PushButtonRepeat(true); //This enables the button repeat 

			if (ImGui::Button("Forward"))
			{
				sceneCamera->ProcessKeyboard(CAMERA::FORWARD, deltaTime);
			}; ImGui::SameLine();

			if (ImGui::Button("Back"))
			{
				sceneCamera->ProcessKeyboard(CAMERA::BACKWARD, deltaTime);
			}; ImGui::SameLine();

			if (ImGui::Button("Left"))
			{
				sceneCamera->ProcessKeyboard(CAMERA::LEFT, deltaTime);
			}; ImGui::SameLine();

			if (ImGui::Button("Right"))
			{
				sceneCamera->ProcessKeyboard(CAMERA::RIGHT, deltaTime);
			}

			// 3. Object movement through Linear and Rotation plus Scale
			ImGui::Text("2: Object Manipulation");
			ImGui::BulletText("Linear Movement");
			if (ImGui::Button("Left"))
			{
				gameobject->MoveObject(Vec3(-1, 0, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Right"))
			{
				gameobject->MoveObject(Vec3(1, 0, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Up"))
			{
				gameobject->MoveObject(Vec3(0, 1, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Down"))
			{
				gameobject->MoveObject(Vec3(0, -1, 0));
				gameobject->UpDateObject();
			}

			// Rotate
			ImGui::BulletText("Rotation");
			if (ImGui::Button("Left"))
			{
				gameobject->RotateObject(5, Vec3(0, 0, 1));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Right"))
			{
				gameobject->RotateObject(-5, Vec3(0, 0, 1));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Up"))
			{
				gameobject->RotateObject(5, Vec3(0, 1, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Down"))
			{
				gameobject->RotateObject(-5, Vec3(0, 1, 0));
				gameobject->UpDateObject();
			}

			// Scale
			ImGui::BulletText("Scale Objects");
			if (ImGui::Button("Left"))
			{
				gameobject->ScaleObject(Vec3(-1, 0, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Right"))
			{
				gameobject->ScaleObject(Vec3(1, 0, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Up"))
			{
				gameobject->ScaleObject(Vec3(0, 1, 0));
				gameobject->UpDateObject();
			} ImGui::SameLine();

			if (ImGui::Button("Down"))
			{
				gameobject->ScaleObject(Vec3(0, -1, 0));
				gameobject->UpDateObject();
			}

			ImGui::End();
		}
	}
	/// 2. This is another Simple window, let say I want to open separate character editor from main editor
	if (show_another_window) {
		if (!ImGui::Begin("Another Window", &show_another_window))
		{
			ImGui::End();
		} else
		{
			ImGui::Text("Hello Another window!");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
			ImGui::End();

		}
	}

	/// 3. Show the ImGui demo window.
	if (show_demo_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	/// ImGui End() - every features has to be before ImGui::End()
	ImGui::End();
}

void Scene0::Render() const{

	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());

	Matrix4 projectionMatrix_ = MMath::perspective(sceneCamera->GetZoom(), aspect, 0.1f, 100.0f);
	Matrix4 viewMatrix_ = sceneCamera->GetViewMatrix();

	/*Matrix4 viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f),
										Vec3(0.0f, 0.0f, 0.0f),
										Vec3(0.0f, 1.0f, 0.0f));*/

	/// ImGUI render
	/// Draw your scene here
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	gameobject->SetLightPos(viewMatrix_ * lightPos);
	gameobject->Render(projectionMatrix_, viewMatrix_, trackball->GetMatrix3());
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

// Commented out because I implemented this feature at ImGui widget

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	//if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN){
	//	trackball->OnLeftMouseDown(SDLEvent.button.x,SDLEvent.button.y);
	//}
	//if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION && 
	//	SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
	//	trackball->OnMouseMove(SDLEvent.button.x,SDLEvent.button.y);
	//}
	//
	//gameobject->HandleEvents(SDLEvent);
}


// Commented out because I added this feature at ImGui widget

void Scene0::processInput(const SDL_Event &SDLEvent, float deltaTime)
{
	//switch (SDLEvent.key.keysym.sym) {

	//case SDLK_w:
	//	sceneCamera->ProcessKeyboard(CAMERA::FORWARD, deltaTime);
	//	printf("Move FORWARD");
	//	break;

	//case SDLK_s:
	//	sceneCamera->ProcessKeyboard(CAMERA::BACKWARD, deltaTime);
	//	printf("Move BACKWARD");
	//	break;
	//case SDLK_a:
	//	sceneCamera->ProcessKeyboard(CAMERA::LEFT, deltaTime);
	//	printf("Move left");
	//	break;

	//case SDLK_d:
	//	sceneCamera->ProcessKeyboard(CAMERA::RIGHT, deltaTime);
	//	printf("Move RIGHT");
	//		break;
	//}
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