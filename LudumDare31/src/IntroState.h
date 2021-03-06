#pragma once
#include "GameState.h"

class CGame;

class CIntroState : public CGameState
{
public:
	void init();
	void cleanup();

	void pause();
	void resume();

	void handleInput(CGame* game, int key, int action);
	void handleInput(CGame* game, double x, double y);
	void update(CGame* game);
	void draw(CGame* game);
	
};

