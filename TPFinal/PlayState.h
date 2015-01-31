#pragma once
#include "GameState.h"

class PlayState : GameState
{
public:
	PlayState(void);
	~PlayState(void);

	virtual void Start();
	virtual void Update();
	virtual void End();
};

