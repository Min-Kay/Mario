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
	virtual void Render(HDC _hdc) {};
	virtual void Release() {};

public:
	void	Set_Result(GAME::RESULT _result) { m_result = _result; };
	void	Result(HDC _hdc);
	void	Show_Win_Lose(HDC _hdc);
	void	Check_State();
	void	Key_Input();


protected:
	GAME::RESULT m_result; 
	bool		isClear;
	bool		isFail;
};

