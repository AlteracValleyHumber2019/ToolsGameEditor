#include <iostream>
#include <fstream>
#include <sstream>
#include "ObjLoader.h"
#include "GameObject.h"
#include <SDL.h>
#include <memory>
#include <map>

#ifndef JSONFILE_H
#define JSONFILE_H


namespace GAME {
	class JSONFile
	{
	public:
		JSONFile();
		~JSONFile();
	

		virtual void OnWrite(std::vector<GameObject*> ScenceModelList);
		virtual std::vector<GameObject*> OnRead();;

	};

}
#endif
