#pragma once
#include "Obj.h"

class CObstacle_Item :
	public CObj
{
public:
	CObstacle_Item();
	virtual ~CObstacle_Item();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;
};

