#pragma once

class CGame;

class CGameState
{
public:
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() {};
	virtual	void resume() {};

	virtual void handleInput(CGame* game) = 0;
	virtual void update(CGame* game) = 0;
	virtual void draw(CGame* game) = 0;	
};
