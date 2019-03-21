
#include "Scene0.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameObject.h"
#include "ObjLoader.h"

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
class FileManager
{
public:
	FileManager();
	~FileManager();
	virtual void OnWrite();
	virtual void OnRead();



	//arifa did this 
	Scene0* CallScence;
	GameObject* gameobject;
	std::vector<Model*> ModelObjlist;

};
#endif
