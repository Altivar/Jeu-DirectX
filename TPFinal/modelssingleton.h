#pragma once

#include "model.h"
#include <list>

class ModelsSingleton
{
public:
	static ModelsSingleton& Instance();
	std::list<Model*> _models;

	Model _modelCube;

private:
	ModelsSingleton(void);
	~ModelsSingleton(void);

	static ModelsSingleton _instance;
	
};

