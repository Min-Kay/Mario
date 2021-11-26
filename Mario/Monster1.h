#pragma once
#include "Monster.h"
class CMonster1 :
	public CMonster
{
public:
	CMonster1();
	virtual ~CMonster1();

	void		Jumping(void);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;
};

