#pragma once
#include "Model.h"

class View
{
protected:
	string type;
public:
	string getType();
	virtual void draw (Model* model) = 0;
};

