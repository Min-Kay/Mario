#pragma once
#include "Obj.h"
class CKoopa_bullet :
	public CObj
{
public:
	CKoopa_bullet();
	virtual ~CKoopa_bullet();

private:
	bool	m_bHide;
	int		m_iCount;


public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

private:
	bool					m_Walk;
	DWORD					m_WalkTime;
	DWORD					m_vaildTime;
	bool					m_vaild;

};

