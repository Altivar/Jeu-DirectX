#pragma once
#include "GameState.h"

class PlayState : GameState
{
public:
	virtual void Start();
	virtual void Update();
	virtual void End();

private:
	Model* _player;
};

