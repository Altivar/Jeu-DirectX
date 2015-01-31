#include "GameManager.h"

//States include
#include "PlayState.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

GameManager GameManager::_instance = GameManager();

GameManager::GameManager(void)
{
	//Models
	_models.clear();
	
	_modelCube.InitModel( ".\\Resources\\cube.obj" , ".\\Resources\\diamond_ore.png" );

	_modelTorus.InitModel( ".\\Resources\\torus.obj" , ".\\Resources\\stonebrick_mossy.png" );

	_modelThing.InitModel( ".\\Resources\\untitled.obj" , ".\\Resources\\redstone_block.png" );

	
	

	Model* m1 = new Model(_modelCube);
	m1->SetTexture(".\\Resources\\stonebrick_mossy.png");
	m1->Translate(0, 0, 5);
	_models.push_back(m1);

	Model* m2 = new Model(_modelCube);
	m2->SetTexture(".\\Resources\\diamond_ore.png");
	m2->Translate(0, 3, 0);
	_models.push_back(m2);

	Model* m3 = new Model(_modelTorus);
	m3->SetTexture(".\\Resources\\stonebrick_mossy.png");
	m3->Translate(0, 0, 1);
	_models.push_back(m3);

	player = new Model(_modelThing);
	player->SetTexture(".\\Resources\\redstone_block.png");
	player->Translate(-2, -1, 0);
	_models.push_back(player);

	//GameStates
	_gameStates.insert(std::pair<std::string, GameState*>("PlayState", (GameState*)new PlayState()));
	LoadGameState("PlayState");
}

void GameManager::Update()
{
	_currentGameState->Update();
}

void GameManager::LoadGameState(string stateStr)
{
	_currentGameState = _gameStates.at(stateStr);
}


GameManager::~GameManager(void)
{
	std::list<Model*>::iterator it = _models.begin();
	while (it != _models.end())
	{
		delete (*it);
		it = _models.erase(it);
	}

}

GameManager& GameManager::Instance()
{
	return _instance;
}
