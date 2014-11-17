#pragma once
#include "Model.h"

class View
{
protected:
	string type;
public:
	static Model* model;
	string getType();
	void setModel(Model* model);
	Model* getModel();
};

