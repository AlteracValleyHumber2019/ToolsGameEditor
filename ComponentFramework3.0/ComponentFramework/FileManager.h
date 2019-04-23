#include <iostream>
#include <fstream>
#include <sstream>
#include "ObjLoader.h"
#include "GameObject.h"

#ifndef FILEMANAGER_H
#define FILEMANAGER_H


namespace GAME {
	class FileManager
	{
	public:
		FileManager();
		~FileManager();
		virtual void OnWrite(std::vector<GameObject*> ScenceModelList);
		virtual void OnRead();






		//arifa did this 
		//Scene0* CallScence;
		//GameObject* gameobject;
		//std::vector<Model*> ModelObjlist;

	};

}
#endif