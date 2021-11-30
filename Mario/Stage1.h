#pragma once
#include "Stage.h"
class CStage1 :
	public CStage
{
public:
	CStage1();
	~CStage1();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC _hdc);
	virtual void Release();

private:
	DWORD		m_Time;
};

