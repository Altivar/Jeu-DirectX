#pragma once

#include "GameState.h"
#include "LevelGenerator.h"
#include "model.h"
#include "point3.h"
#include <string>
#include <list>
#include <map>

class GameState;

class GameManager
{
public:
	//Liste des GameStates
	std::map< string, GameState* > _gameStates;
	GameState* _currentGameState;

	//Models chargés
	Model _modelCube;
	Model _modelTorus;
	Model _modelThing;

	//Models instantiés
	std::list< Model* > _models;
	Model* player;

	//Methods
	static GameManager& Instance();
	void Update();
	void LoadGameState(string stateStr);

private:
	GameManager(void);
	~GameManager(void);

	static GameManager _instance;
};

