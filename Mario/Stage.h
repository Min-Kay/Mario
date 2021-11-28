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

public:
	void	Key_Input();

public:
	void	Init_Ui();
	void	Render_Data(HDC _hdc);

public:
	void	Fall_Down();
	void	Set_Player_To_SavePoint();
	void	Update_SavePoint();
	void	Check_EndLine();

protected:
	GAME::RESULT m_result; 
	bool		isClear;
	bool		isFail;

	TCHAR		score[10] = L"";
	TCHAR		coin[10] = L"";
	TCHAR		life[10] = L"";

	RECT		score_Rect;
	RECT		coin_Rect;
	RECT		life_Rect;
	RECT		EndLine_Rect;

	list<POINT>		savePoint;
	float			endLine;


	HDC				BackgroundDC = NULL;
	HDC				EndLineDC = NULL;

};

