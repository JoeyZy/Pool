#pragma once
#include "Model.h"
#include <vector>

class View
{
protected:
	string type;
public:
	int areaWidth;
	int areaHeight;
	vector<Model*> models;
	string getType();
	void addModel(Model* model);
	vector<Model*> getModels();
};

