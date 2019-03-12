#include "FileManager.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

void FileManager::OnWrite()
{
	

	/*for (int i = 0; i < gameobject.size(); i++)
	{

		gameobject[i]->Update(deltaTime);
	}

	gameobject->Update(deltaTime);
	gameobject->Update(deltaTime);

	std::ofstream info;
	creates a file called Savedata.txt
	info.open("Savedata.txt");


	in this loop it will look though all the model we have then get the name pos , rot etc
	for (int i = 0; i < gameobject.size(); i++)
	{
		std::string Modelname = gameobject[i]->GetMOdelName();
		info << "Model " << Modelname << std::endl;
		info << "pos " << gameobject[i]->GetPos().x << " " << prim->getPos().y << std::endl;
		info << "rot " << gameobject[i]->getAngle() << std::endl;
	}

	info.close();*/
}

void FileManager::OnRead()
{
	//reads file called Savedata.txt

	std::ifstream inFile;

	json j;
	inFile >> j;
	inFile.open("Savedata.txt");



	//make a structure of model have a pos , rot and name 
	struct  ModelData
	{
		std::string ModelName;
		float posX;
		float posY;
		float angle;

	};

	// vector model data (name ,pos, rot)
	std::vector < ModelData> data;

	std::string line;

	// in this loop it will look into the fille and look for a string 
	while (std::getline(inFile, line)) {

		// in this loop it looks for the frist 6 string of charaters to know that there models 
		if (line.substr(0, 6) == "Model ") {
			std::stringstream ss = std::stringstream(line.substr(6));
			std::string modelName;
			ss >> modelName;
			ModelData d;
			d.ModelName = modelName;
			data.push_back(d);
		}


		// in this loop it looks for the frist 4 string of charaters to know that is the model posx and y 
		if (line.substr(0, 4) == "pos ") {
			std::stringstream ss = std::stringstream(line.substr(4));
			float x, y;
			ss >> x >> y;
			data.back().posX = x;
			data.back().posY = y;
		}

		// in this loop it looks for the frist 4 string of charaters to know that is the model rot
		if (line.substr(0, 4) == "rot ") {
			std::stringstream ss = std::stringstream(line.substr(4));
			float x;
			ss >> x;
			data.back().angle = x;
		}

	}


	// in this loop it it will automatitly get data of the model and print the info 
	for (const auto& d : data) {
		std::cout << "Model" << d.ModelName << std::endl;
		std::cout << "Positons x" << d.posX << std::endl;
		std::cout << "Positons y" << d.posY << std::endl;
		std::cout << "Rotation" << d.angle << std::endl;

	}
}
