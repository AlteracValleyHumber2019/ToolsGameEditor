#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL.h>
#include "Vector.h"
#include "Model.h"
#include "shader.h"

namespace GAME {

	class GameObject : public Model
	{
		enum stats { Move, Rotate, Scale };
	public:
		GameObject(char* object_);
		~GameObject();
		void OnDestroy();
		bool OnCreate();
		void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;

		void HandleEvents(const SDL_Event &SDLEvent);
		void MoveObject(Vec3 pos_);
		void RotateObject(float angle_, Vec3 roateAxix);
		void ScaleObject(Vec3 scale_);

		void SetLightPos(const Vec3&);

	private:

		void UpDateObject();
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
		Vec3 position;
		Vec3 rotatePosition;
		float angle;
		Vec3 rotateAxis;
		Vec3 scale;
		stats st;
	};
}
#endif   GAMEOBJECT_H
