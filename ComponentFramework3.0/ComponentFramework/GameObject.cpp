#include "GameObject.h"
#include "ObjLoader.h"
#include "FileManager.h"
#include "JSONFile.h"
#include <stdio.h>
using namespace GAME;

GameObject::GameObject(char*object_):shader(nullptr) {
	ModelName = object_;
	OnCreate();
}



//arifa creates string of files 
GameObject::GameObject(std::string filePath_) {
	//gets file name 
	ModelName = filePath_;
	
	OnCreate();
}



bool GameObject::OnCreate() {

	GAME::ObjLoader obj(ModelName.c_str());

	meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));

	/// Create a shader with attributes
	shader = new GAME::Shader("phongVert.glsl", "phongFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	position = Vec3(0, 0, 0);
	//position = pos;
	rotateAxis = Vec3(0, 0, 1);
	scale = Vec3(1, 1, 1);
	angle = 0;
	modelMatrix = MMath::translate(position.x, position.y, position.z);
	return true;
}

void GameObject::HandleEvents(const SDL_Event &SDLEvent)
{
	switch (SDLEvent.key.keysym.sym) {

	case SDLK_m:
		st = Move;
		break;
	case SDLK_r:
		st = Rotate;
		break;
	case SDLK_p:
		st = Scale;
		break;
	case SDLK_RIGHT:
		if(st == Move)
		{
			MoveObject(Vec3(1,0,0));
			UpDateObject();
			printf("Move RIGHT");
			break;
		}else if(st == Rotate)
		{
			RotateObject(-5, Vec3(0, 0, 1));
			UpDateObject();
			printf("rotate object");
			break;
		}
		else if (st == Scale)
		{
			ScaleObject(Vec3(1, 0, 0));
			UpDateObject();
			printf("scale object");
			break;
		}
	case SDLK_LEFT:
		if(st == Move)
		{
			MoveObject(Vec3(-1, 0, 0));
			UpDateObject();
			printf("Move LEFT");
			break;
		}else if (st == Rotate)
		{
			RotateObject(5, Vec3(0, 0, 1));
			UpDateObject();
			printf("rotate object");
			break;
		}
		else if (st == Scale)
		{
			ScaleObject(Vec3(-1, 0, 0));
			UpDateObject();
			printf("scale object");
			break;
		}
	case SDLK_UP:
		if(st == Move)
		{
			MoveObject(Vec3(0, 1, 0));
			UpDateObject();
			printf("Move UP");
			break;
		}else if(st == Rotate)
		{
			RotateObject(5, Vec3(0, 1, 0));
			UpDateObject();
			printf("rotate object");
			break;
		}
		else if (st == Scale)
		{
			ScaleObject(Vec3(0, 1, 0));
			UpDateObject();
			printf("scale object");
			break;
		}
	case SDLK_DOWN:
		if(st == Move)
		{
			MoveObject(Vec3(0, -1, 0));
			UpDateObject();
			printf("Move DOWN");
			break;
		}else if (st == Rotate)
		{
			RotateObject(-5, Vec3(0, 1, 0));
			UpDateObject();
			printf("rotate object");
			break;
		}
		else if (st == Scale)
		{
			ScaleObject(Vec3(0, -1, 0));
			UpDateObject();
			printf("scale object");
			break;
		}
	case SDLK_j:
		if(st == Move)
		{
			MoveObject(Vec3(0, 0, 1));
			UpDateObject();
			printf("Move FRONT");
			break;
		}else if (st == Rotate)
		{
			RotateObject(5, Vec3(1, 0, 0));
			UpDateObject();
			printf("rotate object");
			break;
		}
		else if (st == Scale)
		{
			ScaleObject(Vec3(0, 0, 1));
			UpDateObject();
			printf("scale object");
			break;
		}
	case SDLK_u:
		if(st == Move)
		{
			MoveObject(Vec3(0, 0, -1));
			UpDateObject();
			printf("Move BACK");
			break;
		}else if (st == Rotate)
		{
			RotateObject(-5, Vec3(1, 0, 0));
			UpDateObject();
			printf("rotate object");
			break;
		}
		else if (st == Scale)
		{
			ScaleObject(Vec3(0, 0, -1));
			UpDateObject();
			printf("scale object");
			break;
		}
	}
}
void GameObject::MoveObject(Vec3 pos_)
{
	position += pos_;
}
void GameObject::RotateObject(float angle_, Vec3 roateAxix_)
{
	angle += angle_;
	rotateAxis = roateAxix_;
}
void GameObject::ScaleObject(Vec3 scale_)
{
	scale += scale_;
}
void GameObject::UpDateObject()
{
	
	modelMatrix = MMath::translate(0, 0, 0);
	modelMatrix *= MMath::rotate(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	modelMatrix *= MMath::scale(scale.x, scale.y, scale.z);
	modelMatrix *= MMath::translate(position.x, position.y, position.z);
	
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
