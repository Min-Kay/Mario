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
	RECT&		Get_CollisionRect() { return On_Collision_Rect; }
	void		Set_OnBlock(bool _bool) { Above_Block = _bool; }
	void		Set_CollisionY(float _y) { m_CollisionY = _y; }
	float&		Get_CollisionY() { return m_CollisionY; }

private:
	void		Cal_MaxJumpTime(float* _fMaxJumpTime);
	void		Key_Input(void);
	void		Jumping(void);
	void		Show_Dying_Anim();

	void		Set_Vaild();
	void		Update_Collision_Rect();

private:
	RECT					On_Collision_Rect;
	float					m_CollisionY;
	bool					Above_Block;
	bool					Jump_On;

	bool					isVaild;
	DWORD					m_VaildTime;
	float					CoolTime;
 
	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fJumpTime;
	float					m_fMaxJumpTime;
	float					m_fTime;
	bool					m_walk;
	DWORD					m_JumpTime;
	bool					init_JumpTime;
	bool					is_Not_Down;
	bool					is_Collision;

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

