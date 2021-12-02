#pragma once
#include "Stage.h"
class CStage3 :
	public CStage
{
public:
	CStage3();
	~CStage3();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC _hdc);
	virtual void Release();

};

