#ifndef Scene0_H
#define Scene0_H

#include "Scene.h"
#include "Window.h"
#include "GameObject.h"
#include "Camera.h"
#include "vector"
#include "FileManager.h"
#include "JSONFile.h"

namespace GAME {
	/// Forward casting
	class Trackball;
	class Model0;

	class Scene0 : public Scene  {
	protected:
		Matrix4 projectionMatrix_;
	public:
		explicit Scene0(Window& windowRef);
		virtual ~Scene0();


		/// Delete these possible default constructors and operators  
		Scene0(const Scene0&) = delete;
		Scene0(Scene0 &&) = delete;
		Scene0& operator=(const Scene0 &) = delete;
		Scene0& operator=(Scene0 &&) = delete;

		virtual bool OnCreate() ;
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render();
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int, const int);
		virtual void processInput(const SDL_Event &SDLEvent, float deltaTime);
		virtual void processMouseInput(const SDL_Event &SDLEvent);
		


		//arifa was here
		GameObject* gameobject;
		std::vector<GameObject*> ScenceModelList;
		std::map<std::string, std::vector<GameObject*>> myOBJs;



	private:
		void placeObjects(char*object_);
		Vec3 lightPos;
		Model0 *model0;
		Trackball *trackball;
		Camera* sceneCamera;
		bool firstMouse;
		int lastX, lastY;
		Matrix4 viewMatrix_;
		Vec3 getObjectLocation(float mouseX, float mouseY);
		void ObjectSelection();
	};
}
#endif