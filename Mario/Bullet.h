#pragma once
#include "Obj.h"
#include "Enum.h"
class CBullet : public CObj
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

	void		Jumping(void);

private:
	int				m_iCount;	// ���� ���� Ƚ�� ������ ����
	bool			m_bJump;
	float			m_fJumpY;
	float			m_fJumpPower;
	float			m_fTime;

	float			m_fSubScroll;

private:
	int m_AnimNum = 0;
};

