#pragma once
#include "GameManager.h"

class GameState
{
public:
	GameState(void);
	~GameState(void);

	virtual void Start() {}
	virtual void Update() {}
	virtual void End() {}
};

