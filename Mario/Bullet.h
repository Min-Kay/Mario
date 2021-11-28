#pragma once
#include "Obj.h"
#include "Enum.h"
class CBullet :	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;

	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;
private:
	int m_AnimNum = 0; 

};

