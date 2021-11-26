#pragma once

#include "Obj.h"
#include "Enum.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();


private:
	void		Key_Input(void);
	void		Jumping(void);
	
private:
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
};

