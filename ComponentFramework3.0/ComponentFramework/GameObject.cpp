#include "GameObject.h"
#include "ObjLoader.h"
#include "FileManager.h"
#include "JSONFile.h"
#include <stdio.h>
#include <iostream>
using namespace GAME;

GameObject::GameObject(char*object_):shader(nullptr) {
	//(arifa)
	ModelName = object_;
	OnCreate();
}
GameObject::GameObject(char*object_, Vec3 Ipos_) : shader(nullptr) {
	object = object_;
	pos = Ipos_;
	OnCreate();
}



//arifa creates string of files 
GameObject::GameObject(std::string filePath_) {
	//gets file name 
	ModelName = filePath_;

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


	//get the min vertice in the created object
	GetMin(obj.vertices);
	//get the max vertice in the created object
	GetMax(obj.vertices);

	MakeSelectBox();


	ObjectSelected = true;

	//position = pos;
	position = Vec3(0, 0, 0);
	rotateAxis = Vec3(0, 0, 1);
	scale = Vec3(1, 1, 1);
	angle = 0;
	modelMatrix = GetCenter();
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
	Vec3 Tempmin = verts[0];

	//loop through the vector of vertices and compare them if they are less or equal to then the min now equals that vert.
	for (int i = 1; i < verts.size(); i++)
	{
		if (verts[i].x <= Tempmin.x) { Tempmin.x = verts[i].x; }
		if (verts[i].y <= Tempmin.y) { Tempmin.y = verts[i].y; }
		if (verts[i].z <= Tempmin.z) { Tempmin.z = verts[i].z; }
		minX = Tempmin;

	}
	std::cout << "min = " << Tempmin.x << ": " << Tempmin.y << ": " << Tempmin.z << std::endl;
}
void GAME::GameObject::GetMax(std::vector<Vec3> Verts)
{
	//create a vec based on the first vertice in the vector
	Vec3 TempMax = Verts[0];

	//loop through the vector of vertices and compare them if they are greater then or equal to then the Max now equals that vert.
	for (int i = 0; i < Verts.size(); i++)
	{
		if (Verts[i].x >= TempMax.x) { TempMax.x = Verts[i].x; }
		if (Verts[i].y >= TempMax.y) { TempMax.y = Verts[i].y; }
		if (Verts[i].z >= TempMax.z) { TempMax.z = Verts[i].z; }
		maxX = TempMax;

	}
	std::cout << "min = " << TempMax.x << ": " << TempMax.y << ": " << TempMax.z << std::endl;
}
void GAME::GameObject::MakeSelectBox()
{
	SelectBox.push_back(Vec3(minX.x, minX.y, minX.z));
	SelectBox.push_back(Vec3(minX.x, minX.y, maxX.z));
	SelectBox.push_back(Vec3(minX.x, maxX.y, minX.z));
	SelectBox.push_back(Vec3(minX.x, maxX.y, maxX.z));

	SelectBox.push_back(Vec3(maxX.x, maxX.y, maxX.z));
	SelectBox.push_back(Vec3(maxX.x, maxX.y, minX.z));
	SelectBox.push_back(Vec3(maxX.x, minX.y, maxX.z));
	SelectBox.push_back(Vec3(maxX.x, minX.y, minX.z));

	std::cout << "pont 1: " << SelectBox[7].x << ", " << SelectBox[7].y << ", " << SelectBox[7].z << std::endl;
}

Matrix4 GAME::GameObject::GetCenter()
{
	Vec3 temp = Vec3(0, 0, 0);
	for (int i = 0; i < SelectBox.size(); i++)
	{
		temp += SelectBox[i];
	}

	temp = temp / (SelectBox.size() * 1.0f);
	return MMath::translate(-temp.x, -temp.y, -temp.z);
	std::cout << "temp size = " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;
}


void GameObject::UpDateObject()
{
	modelMatrix = GetCenter();
	modelMatrix *= MMath::rotate(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	modelMatrix *= MMath::scale(scale.x, scale.y, scale.z);
	modelMatrix *= MMath::translate(pos.x, pos.y, pos.z);
}

void GameObject::SetLightPos(const Vec3& lightPos_) {
	lightPos = lightPos_;
}

bool GameObject::CheckCollisonSelection(int moseX_, int mouseY_)
{
	//if(moseX_ < SelectBox[0].x && )
	return true;
}
void GameObject::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix) const
{
	glUseProgram(shader->getProgram());
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, modelMatrix * viewMatrix);
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
