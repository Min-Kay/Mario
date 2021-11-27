#pragma once
#include "Include.h"
#include "framework.h"
class CGame
{
public:
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Late_Update() {};
	virtual void Render(HDC _hdc) {};
	virtual void Release() {};

public:
	GAME::ID	Get_GameNum() { return m_GameNum; };
	void		Set_GameNum(GAME::ID i) { m_GameNum = i; };

protected:
	GAME::ID		m_GameNum;
};

