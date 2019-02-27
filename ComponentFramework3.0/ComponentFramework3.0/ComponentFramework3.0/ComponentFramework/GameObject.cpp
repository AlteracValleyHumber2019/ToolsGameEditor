#include "GameObject.h"
#include "ObjLoader.h"
#include <stdio.h>
using namespace GAME;

GameObject::GameObject(char*object_):shader(nullptr) {
	object = object_;
	OnCreate();
}
bool GameObject::OnCreate() {

	GAME::ObjLoader obj(object);	

	meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));

	/// Create a shader with attributes
	shader = new GAME::Shader("phongVert.glsl", "phongFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	modelMatrix = MMath::translate(0.0f, 0.3f, 0.0f);
	return true;
}

void GameObject::HandleEvents(const SDL_Event &SDLEvent)
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		//printf("Calling SDL_PollEvent");
		/*pos.x += 1;
		MoveObject(pos);*/
		printf("%d", event.type);
		if (event.type == SDL_KEYDOWN) {
			printf("Move RIGHT");
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT:
				pos.y += 1;
				MoveObject(pos);
				printf("Move RIGHT");
				break;
			case SDLK_LEFT:
				pos.y -= 1;
				MoveObject(pos);
				break;
			case SDLK_UP:
				pos.x += 1;
				MoveObject(pos);
				break;
			case SDLK_DOWN:
				pos.x -= 1;
				MoveObject(pos);
				break;
			case SDLK_w:
				pos.z += 1;
				MoveObject(pos);
				break;
			case SDLK_s:
				pos.z -= 1;
				MoveObject(pos);
				break;
			}
		}
	}

}
void GameObject::MoveObject(Vec3 pos_)
{
	pos += pos_;
	modelMatrix = MMath::translate(pos.x, pos.y, pos.z);
}
void GameObject::RotateObject()
{

}
void GameObject::ScaleObject()
{

}

void GameObject::SetLightPos(const Vec3& lightPos_) {
	lightPos = lightPos_;
}

void GameObject::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix) const
{
	glUseProgram(shader->getProgram());
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	glUniform3fv(lightPosID, 1, lightPos);
	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO
}
void GameObject::OnDestroy()
{
	glDeleteBuffers(1, &vbo);
	if (shader) delete shader;

	for (Mesh* mesh : meshes) {
		if (mesh) delete mesh;
	}
}

GameObject::~GameObject()
{
	OnDestroy();
}
