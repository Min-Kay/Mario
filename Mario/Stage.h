#pragma once
#include "Game.h"
#include "Include.h"

class CStage :
    public CGame
{
public:
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Late_Update() {};
	virtual void Render() {};
	virtual void Release() {};

public:
	void	Set_Result();
	void	Result();
	void	Show_Win_Lose();


protected:
	GAME::RESULT m_result; 
};

