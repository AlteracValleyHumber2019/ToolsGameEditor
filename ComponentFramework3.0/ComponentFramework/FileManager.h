
#include "Scene0.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameObject.h"
#include "ObjLoader.h"
#include "Scene0.h"

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
	GameObject* gameobject;
	std::vector<Model*> ModelObjlist;

};
#endif
