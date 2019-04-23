#include "FileManager.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Scene0.h"
#include "GameObject.h"
#include "JSONFile.h"


using json = nlohmann::json;

using namespace GAME;
using namespace MATH;



GAME::JSONFile::JSONFile()
{
}

GAME::JSONFile::~JSONFile()
{
}

void GAME::JSONFile::OnWrite(std::vector<GameObject*> ScenceModelList)
{
	json j;

	for (int i = 0; i < ScenceModelList.size(); i++)
	{
		
		j["object" + std::to_string(i)]["type"] = ScenceModelList[i]->GetMOdelName();
		j["object" + std::to_string(i)]["Pos x"] = ScenceModelList[i]->GetPos().x;
		j["object" + std::to_string(i)]["Pos Y"] = ScenceModelList[i]->GetPos().y;
		j["object" + std::to_string(i)]["Pos Z"] = ScenceModelList[i]->GetPos().z;



		j["object" + std::to_string(i)]["RotateAxis X"] = ScenceModelList[i]->GetRotateAxis().x;
		j["object" + std::to_string(i)]["RotateAxis Y"] = ScenceModelList[i]->GetRotateAxis().y;
		j["object" + std::to_string(i)]["RotateAxis Z"] = ScenceModelList[i]->GetRotateAxis().z;

		j["object" + std::to_string(i)]["rotatePosition X"] = ScenceModelList[i]->GetrotatePosition().x;
		j["object" + std::to_string(i)]["rotatePosition Y"] = ScenceModelList[i]->GetrotatePosition().y;
		j["object" + std::to_string(i)]["rotatePosition Z"] = ScenceModelList[i]->GetrotatePosition().z;

		j["object" + std::to_string(i)]["ScaleX"] = ScenceModelList[i]->GetScale().x;
		j["object" + std::to_string(i)]["ScaleY"] = ScenceModelList[i]->GetScale().y;
		j["object" + std::to_string(i)]["ScaleZ"] = ScenceModelList[i]->GetScale().z;

		j["object" + std::to_string(i)]["angle"] = ScenceModelList[i]->Getangle();
	}
	std::cout << j.dump(2) << std::endl;
	std::ofstream o("saveinfo.json");
	o << j << std::endl;
	o.close();
}

std::vector<GameObject*> GAME::JSONFile::OnRead()
{
	std::vector<GameObject*> ScenceModelList;

	//Creates a json variable
	json j;

	//Opening and reading from a json file
	std::ifstream i("saveinfo.json");
	i >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		GameObject* gameobject = new GameObject(j[it.key()]["type"]);

		gameobject->SetPos(MATH::Vec3(j[it.key()]["Pos x"], j[it.key()]["Pos Y"], j[it.key()]["Pos Z"]));
		gameobject->SetRotateAxis(MATH::Vec3(j[it.key()]["RotateAxis X"], j[it.key()]["RotateAxis Y"], j[it.key()]["RotateAxis Z"]));
		gameobject->SetrotatePosition(MATH::Vec3(j[it.key()]["rotatePosition X"], j[it.key()]["rotatePosition Y"], j[it.key()]["rotatePosition Z"]));
		gameobject->SetScale(MATH::Vec3(j[it.key()]["ScaleX"], j[it.key()]["ScaleY"], j[it.key()]["ScaleZ"]));
		gameobject->Setangle(j[it.key()]["angle"]);
	
		ScenceModelList.push_back(gameobject);

	}
	//Closes the file
	i.close();

	return ScenceModelList;

}
