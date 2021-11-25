#pragma once
#include "Game.h"
class CMenu :
    public CGame
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render();
	virtual void Release();
};

