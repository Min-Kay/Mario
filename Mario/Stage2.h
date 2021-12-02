#pragma once
#include "Stage.h"
class CStage2 :
	public CStage
{
public:
	CStage2();
	~CStage2();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC _hdc);
	virtual void Release();

private:
	DWORD		m_Time;
};

