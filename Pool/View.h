#pragma once
#include "Model.h"

class View
{
	Model *model;
public:
	void setModel(Model *model);
	Model* getModel();
};

