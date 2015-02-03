#pragma once

#include "GameManager.h"
#include "model.h"
#include "point3.h"
#include <string>
#include <vector>

class LevelGenerator
{
public:
	//Methods
	static LevelGenerator*& Instance();
	void Start();
	void Update();
	void AddPlateformToList(Model* mdl);

private:
	LevelGenerator(void);
	~LevelGenerator(void);

	static LevelGenerator* _instance;

	//Models instantiés
	std::vector< Model* > _plateformList;
	std::vector< Model > _plateformUse;
	
	float nextUpdate;
};

