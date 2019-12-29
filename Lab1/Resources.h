#pragma once
#include <map>
#include <string>
#include <iostream>
#include "obj_loader.h"

using namespace std;

class Resources
{
public:
	Resources();
	~Resources();
	const string RESOURCES = "D:\\git\\GP2-Coursework\\res\\";

	/* Using the name, sees if the model is already saved in the models map. If not, load from file and cache. */
	IndexedModel* getModel(string name);
private: 
	map<string, IndexedModel*> models;
};

