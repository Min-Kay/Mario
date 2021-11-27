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
	virtual void	Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) {}; // (CObj* pObj)

	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

	OBJ::ID		Get_ID() { return m_eID; }
	bool		Get_Dead() { return m_bDead; }


	bool		Screen_Out_Check();

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
	OBJ::ID			m_eID;
};

