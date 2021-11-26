#pragma once
#include "Game.h"
#include "GameButton.h"
#include <functional>

class CMenu :
	public CGame
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	void StartGame();
	void ExitGame();

private:
	TCHAR		szBuff1[32];
	TCHAR		szBuff2[32];
	HFONT		hFont, oldFont;
	HBRUSH		brush = NULL;
	float		fX = 270.f;
	float		fY = 100.f;
	CGameButton m_StartButton;
	CGameButton m_ExitButton;
};

