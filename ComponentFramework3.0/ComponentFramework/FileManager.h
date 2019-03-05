#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "GameObject.h"

class FileManager
{
public:
//	FileManager(std::string filePath_);
	virtual void OnSave();
	virtual void OnLoad();
	FileManager(std::string filePath_);
	~FileManager();
	

private:
//	std::vector<GameObject*> models;

};
#endif
