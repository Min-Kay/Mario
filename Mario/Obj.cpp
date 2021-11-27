#include "framework.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CObj::~CObj()
{
}

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::Set_PosX(float _fX)
{
	m_tInfo.fX += _fX;
}

void CObj::Set_PosY(float _fY)
{
	m_tInfo.fY += _fY;
}
void CObj::Set_PosY1(float _fY)
{
	m_tInfo.fY = _fY;
}
void CObj::Set_Direction(DIR::DIR e_Dir)
{
	m_eDir = e_Dir;
}

bool CObj::Screen_Out_Check()
{
	if (0 > m_tInfo.fX ||
		0 > m_tInfo.fY ||
		WINCX < m_tInfo.fX ||
		WINCY < m_tInfo.fY)
		return true;
	return false;
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}