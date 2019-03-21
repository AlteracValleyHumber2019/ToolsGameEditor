#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Model.h"
#include <SDL.h>
#include "Vector.h"
#include "shader.h"


namespace GAME {
	class GameObject : public Model
	{
	public:
		GameObject(char* object_);
		
		//ModelName list  //arifa did this
		GameObject(std::string filePath_);

		~GameObject();
		void OnDestroy();
		bool OnCreate();
		void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;

		void HandleEvents(const SDL_Event &SDLEvent);
		void MoveObject(Vec3 pos_);
		void RotateObject();
		void ScaleObject();

		void SetLightPos(const Vec3&);
	private:

		GAME::Shader *shader;
		GLuint vbo;
		GLuint vao;
		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;

		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;
		GLint lightPosID;
		Vec3 lightPos;
		char* object;

	};
}
#endif   GAMEOBJECT_H
