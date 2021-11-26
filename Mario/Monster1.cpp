#include "framework.h"
#include "Monster1.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

CMonster1::CMonster1()
{
}


CMonster1::~CMonster1()
{
}
void CMonster1::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fX = 600.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 2.f;

	m_fTime = 5.f;
	m_bJump = false;
	m_fJumpPower = 15.f;
	m_fJumpY = 0.f;
}


int CMonster1::Update(void)
{
	DWORD m_dwTime = 0;

	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed;

	if (m_dwTime + 5000 <= GetTickCount()) // 3초에 한번 씩 수행
	{
		m_fJumpY = m_tInfo.fY;
		m_bJump = true;

		m_dwTime = GetTickCount();
	}
	Jumping();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster1::Jumping(void)
{
	float		fY = 0.f;

	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (true == m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.2f;

		if (bLineCol && fY + 10 < m_tInfo.fY + (m_tInfo.fCY * 0.5f))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		}
	}

	else if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
}

void CMonster1::Late_Update(void)
{
	if ((0 >= m_tRect.left) || (WINCX  <= m_tRect.right))
	m_fSpeed *= -1.f;
}

void CMonster1::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Ellipse(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right + ScrollX, m_tRect.bottom);
}

void CMonster1::Release(void)
{

}
void CMonster1::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::UP:
			m_bDead = true;
			break;
		}
	}
}