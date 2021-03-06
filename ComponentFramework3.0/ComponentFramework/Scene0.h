#ifndef Scene0_H
#define Scene0_H

#include "Scene.h"
#include "Window.h"
#include "GameObject.h"
#include "Camera.h"
#include "FileManager.h"

namespace GAME {
	/// Forward casting
	class Trackball;
	class Model0;

	class Scene0 : public Scene  {
	protected:
		
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
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int, const int);
		virtual void processInput(const SDL_Event &SDLEvent, float deltaTime);
		virtual void processMouseInput(const SDL_Event &SDLEvent);
	

		//arifa was here
		GameObject* gameobject;
		std::vector<Model*> ScenceModelList;

	private:
		Vec3 lightPos;
		Model0 *model0;
		Trackball *trackball;
		GameObject* gameobject;
		Camera* sceneCamera;
		bool firstMouse;
		int lastX, lastY;
		
		////arifa 
		//std::vector<Model*> models;
	};
}
#endif