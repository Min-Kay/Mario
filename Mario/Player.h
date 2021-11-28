#pragma once

#include "Obj.h"
#include "Enum.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Jump(bool _bool) { m_bJump = _bool; }

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Show_Dying_Anim();
private:
	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;
	bool					m_walk;

	bool					m_bRun;
	float					m_fRunSpeed;

	float					m_total = 0.f;
	DWORD					m_DeadTime = 0;

	DWORD					m_WalkTime = 0; 
	float					m_WalkAnim;
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;
};

