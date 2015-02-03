#include "PlayState.h"
#include <conio.h>

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

void PlayState::Start()
{
	_player = GameManager::Instance().player;
}

void PlayState::Update()
{
	//Input
	if(GetAsyncKeyState(VK_LEFT))
	{
		GameManager::Instance().player->Translate(-0.1f, 0.0f, 0.0f);
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		GameManager::Instance().player->Translate(0.1f, 0.0f, 0.0f);
	}
	if(GetAsyncKeyState(VK_UP))
	{
		GameManager::Instance().player->Translate(0.0f, 0.1f, 0.0f);
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		GameManager::Instance().player->Translate(0.0f, -0.1f, 0.0f);
	}

	//Gameplay
	_player->Translate(0.0f, 0.0f, 0.1f);

	//LevelGenerator Update
	LevelGenerator::Instance()->Update();
}

void PlayState::End()
{

}