#include "GameObject.h"
#include <iostream>
#include "ObjLoader.h"
#include <stdio.h>
using namespace GAME;

GameObject::GameObject(char*object_):shader(nullptr) {
	object = object_;
	OnCreate();
}
GameObject::GameObject(char*object_, Vec3 Ipos_) : shader(nullptr) {
	object = object_;
	pos = Ipos_;
	OnCreate();
}
bool GameObject::OnCreate() {

	GAME::ObjLoader obj(object);	

	meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));

	float tempX;
	//get the min vertice in the created object
	GetMin(obj.vertices);
	//get the max vertice in the created object
	GetMax(obj.vertices);

	ObjectSelected = true;
	/// Create a shader with attributes
	shader = new GAME::Shader("phongVert.glsl", "phongFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");

	//position = pos;
	rotateAxis = Vec3(0, 0, 1);
	scale = Vec3(1, 1, 1);
	angle = 0;
	modelMatrix = MMath::translate(pos.x, pos.y, pos.z);
	return true;
}

void GameObject::HandleEvents(const SDL_Event &SDLEvent)
{
	if (ObjectSelected == true) {
		switch (SDLEvent.key.keysym.sym) {

		case SDLK_y:
			st = Move;
			break;
		case SDLK_u:
			st = Rotate;
			break;
		case SDLK_i:
			st = Scale;
			break;
		case SDLK_RIGHT:
			if (st == Move)
			{
				MoveObject(Vec3(1, 0, 0));
				UpDateObject();
				printf("Move RIGHT");
				break;
			}
			else if (st == Rotate)
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
			if (st == Move)
			{
				MoveObject(Vec3(-1, 0, 0));
				UpDateObject();
				printf("Move LEFT");
				break;
			}
			else if (st == Rotate)
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
			if (st == Move)
			{
				MoveObject(Vec3(0, 1, 0));
				UpDateObject();
				printf("Move UP");
				break;
			}
			else if (st == Rotate)
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
			if (st == Move)
			{
				MoveObject(Vec3(0, -1, 0));
				UpDateObject();
				printf("Move DOWN");
				break;
			}
			else if (st == Rotate)
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
		case SDLK_n:
			if (st == Move)
			{
				MoveObject(Vec3(0, 0, 1));
				UpDateObject();
				printf("Move FRONT");
				break;
			}
			else if (st == Rotate)
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
		case SDLK_h:
			if (st == Move)
			{
				MoveObject(Vec3(0, 0, -1));
				UpDateObject();
				printf("Move BACK");
				break;
			}
			else if (st == Rotate)
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
}
void GameObject::MoveObject(Vec3 pos_)
{
	pos += pos_;
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

void GAME::GameObject::GetMin(std::vector<Vec3> verts)
{

	//create a vec based on the first vertice in the vector
	Vec3 min = verts[0];
	
	//loop through the vector of vertices and compare them if they are less or equal to then the min now equals that vert.
	for (int i = 0; i < sizeof(verts); i++)
	{
		if (verts[i].x <= min.x) { min.x = verts[i].x; }
		if (verts[i].y <= min.y) { min.y = verts[i].y; }
		if (verts[i].z <= min.z) { min.z = verts[i].z; }
		std::cout << "min = " << min.x << ": " << min.y << ": " << min.z << std::endl;
	}
}

void GAME::GameObject::GetMax(std::vector<Vec3> Verts)
{
	//create a vec based on the first vertice in the vector
	Vec3 Max = Verts[0];

	//loop through the vector of vertices and compare them if they are greater then or equal to then the Max now equals that vert.
	for (int i = 0; i < sizeof(Verts); i++)
	{
		if (Verts[i].x >= Max.x) { Max.x = Verts[i].x; }
		if (Verts[i].y >= Max.y) { Max.y = Verts[i].y; }
		if (Verts[i].z >= Max.z) { Max.z = Verts[i].z; }
		std::cout << "min = " << Max.x << ": " << Max.y << ": " << Max.z << std::endl;
	}
}


void GameObject::UpDateObject()
{
	modelMatrix = MMath::translate(0, 0, 0);
	modelMatrix *= MMath::rotate(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	modelMatrix *= MMath::scale(scale.x, scale.y, scale.z);
	modelMatrix *= MMath::translate(pos.x, pos.y, pos.z);
}

void GameObject::SetLightPos(const Vec3& lightPos_) {
	lightPos = lightPos_;
}
bool GameObject::CheckCollisonSelection(int moseX_, int mouseY_)
{

	return false;
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
