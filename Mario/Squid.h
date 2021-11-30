#pragma once
#include "Monster.h"
class CSquid :
	public CMonster
{
public:
	CSquid();
	virtual ~CSquid();

	void		Jumping(void);

protected:
	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

private:
	bool					m_Walk;
	DWORD					m_WalkTime = 0;
};

