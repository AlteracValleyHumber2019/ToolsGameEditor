#include "FileManager.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include "Scene0.h"
#include "GameObject.h"

/*

the file manager  should have empty vector structer  what need to do is dependeding on the
situtation it will read and write or it will take a refernce from the into a file




*/
using json = nlohmann::json;

using namespace GAME;
using namespace MATH;

FileManager::FileManager()
{

}


FileManager::~FileManager()
{

}

void FileManager::OnWrite(std::vector<GameObject*> ScenceModelList)
{
	

	std::ofstream info;
	//creates a file called Savedata.txt
	info.open("Savedata.txt");


	//in this loop it will look though all the model we have then get the name pos , rot etc
	for (int i = 0; i < ScenceModelList.size(); i++)
	{
		std::string Modelname = ScenceModelList[i]->GetMOdelName();
		info << "Model " << Modelname << std::endl;

		///add getters
		info << "pos " << ScenceModelList[i]->GetPos().x << " " << ScenceModelList[i]->GetPos().y << std::endl;
		info << "angle " << ScenceModelList[i]->Getangle() << std::endl;
		info << "RotateAxis " << ScenceModelList[i]->GetRotateAxis().x << " " << ScenceModelList[i]->GetRotateAxis().y << std::endl;
		info << "rotatePosition " << ScenceModelList[i]->GetrotatePosition().x << " " << ScenceModelList[i]->GetrotatePosition().y << std::endl;
		info << "Scale " << ScenceModelList[i]->GetScale().x<< " " << ScenceModelList[i]->GetScale().y << std::endl;
	}

	OnRead();
	info.close();
}

void FileManager::OnRead()
{
	//reads file called Savedata.txt

	std::ifstream inFile;

	//json j;
	//inFile >> j;
	inFile.open("Savedata.txt");


	//make a structure of model have a pos , rot and name 
	struct  ModelData
	{
		std::string ModelName;
		float posX;
		float posY;
		float angle;
		float RotateAxisX;
		float RotateAxisY;
		float rotatePositionX;
		float rotatePositionY;
		float ScaleX;
		float ScaleY;


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
		if (line.substr(0, 4) == "angle  ") {
			std::stringstream ss = std::stringstream(line.substr(4));
			float x;
			ss >> x;
			data.back().angle = x;
		}


		// in this loop it looks for the frist 4 string of charaters to know that is the model rot
		if (line.substr(0, 11) == "Rotation Pos  ") {
			std::stringstream ss = std::stringstream(line.substr(4));
			float x, y;
			ss >> x>>y;
			data.back().rotatePositionX = x;
			data.back().rotatePositionY = y;
		}

		// in this loop it looks for the frist 4 string of charaters to know that is the model rot
		if (line.substr(0, 11) == "Rotate Axis  ") {
			std::stringstream ss = std::stringstream(line.substr(4));
			float x, y;
			ss >> x >> y;
			data.back().RotateAxisX= x;
			data.back().RotateAxisY = y;
		}


		if (line.substr(0, 11) == "Scale ") {
			std::stringstream ss = std::stringstream(line.substr(4));
			float x, y;
			ss >> x >> y;
			data.back().ScaleX = x;
			data.back().ScaleY = y;
		}






	}


	// in this loop it it will automatitly get data of the model and print the info 
	for (const auto& d : data) {
		std::cout << "Model" << d.ModelName << std::endl;
		std::cout << "Positons x" << d.posX << std::endl;
		std::cout << "Positons y" << d.posY << std::endl;
		std::cout << "angle" << d.angle << std::endl;
		std::cout << "Rotation Pos X" << d.rotatePositionX << std::endl;
		std::cout << "Rotation Pos Y" << d.rotatePositionY << std::endl;
		std::cout << "Rotate AxisX" << d.RotateAxisX << std::endl;
		std::cout << "Rotate AxisY" << d.RotateAxisY << std::endl;
		std::cout << "Scale" << d.ScaleX << std::endl;
		std::cout << "Scale" << d.ScaleY << std::endl;

	}
}
