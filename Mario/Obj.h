#pragma once

#include "Define.h"
#include "Struct.h"
#include "Enum.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Pos(float _fX, float _fY);
	void			Set_Dead(bool _bool) { m_bDead = _bool; }
	void			Set_PosX(float _fX);
	void			Set_PosY(float _fY);
	void			Set_PosY1(float _fY);
	void			Set_Direction(DIR::DIR e_Dir);
	virtual void	Set_Collision(CObj* _obj, DIR::DIR _eDIR) {};

	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

	OBJID::ID		Get_ID() { return m_eID; }

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

	void				Update_Rect(void);

protected:
	RECT			m_tRect;
	INFO			m_tInfo;
	float			m_fSpeed;
	bool			m_bDead;	
	DIR::DIR		m_eDir;
	OBJID::ID		m_eID;
	bool			m_bRide;
};

