#include "framework.h"
#include "Monster.h"
#include "LineMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}


void CMonster::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 2.f;

	m_fTime = 0.f;
	m_bJump = false;
	m_fJumpPower = 50.f;
	m_fJumpY = 0.f;
}


int CMonster::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);


	m_tInfo.fX += m_fSpeed;

	if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);

	Jumping();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Jumping(void)
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

void CMonster::Late_Update(void)
{
	if ((0 >= m_tRect.left) || (WINCX  <= m_tRect.right))
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	
}
void CMonster::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
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
