#include "Squid.h"
#include "Manager.h"

CSquid::CSquid()
{
}


CSquid::~CSquid()
{
}
void CSquid::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 2.f;

	m_fTime = 0.f;
	m_bJump = false;
	m_fJumpPower = 50.f;
	m_fJumpY = 0.f;

	m_eDir = DIR::RIGHT;
	m_State = STATE::IDLE;

	CBmpMgr::Get_Instance()->Insert_Bmp(SQUID_L_BMP, SQUID_L_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(SQUID_R_BMP, SQUID_R_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(SQUID_DIE_BMP, SQUID_DIE_KEY);
}


int CSquid::Update(void)
{
	if (m_bDead)
	{
		m_tInfo.fY += FALL_DOWN;
		if (m_tInfo.fY >= WINCY)
		{
			m_State = STATE::DIE;
			return OBJ_DEAD;
		}
		Update_Rect();
		return OBJ_NOEVENT;
	}

	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	m_tInfo.fX += m_fSpeed;

	if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);

	Jumping();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSquid::Jumping(void)
{
	if (m_bDead)
		return;

	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.2f;
		m_State = STATE::JUMP;

		if (bLineCol && fY + 10 < m_tInfo.fY + (m_tInfo.fCY * 0.5f))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
			m_State = STATE::IDLE;

		}
	}
	else if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
	else
	{
		m_fSpeed *= -1.f;
		m_eDir = DIR::LEFT ? DIR::RIGHT : DIR::LEFT;
	}
}

void CSquid::Late_Update(void)
{

}

void CSquid::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC = NULL;
	switch (m_State)
	{
	case STATE::IDLE:
		if (m_Walk)
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(SQUID_L_KEY);
			if (m_WalkTime + 100.f < GetTickCount())
			{
				m_WalkTime = GetTickCount();
				m_Walk = !m_Walk;
			}
		}
		else
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(SQUID_R_KEY);
			if (m_WalkTime + 100.f < GetTickCount())
			{
				m_WalkTime = GetTickCount();
				m_Walk = !m_Walk;
			}
		}
		break;
	case STATE::DIE:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(SQUID_DIE_KEY);
		break;
	default:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(SQUID_L_KEY);
		break;
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CSquid::Release(void)
{

}
void CSquid::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (m_bDead)
		return;

	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::UP:
			m_bDead = true;
			CDataMgr::Get_Instance()->Add_Score(100);
			break;
		default:
			break;
		}
	}
	else if (_eID == OBJ::BULLET)
	{
		m_bDead = true;
		CDataMgr::Get_Instance()->Add_Score(100);
	}
	else if (_eID == OBJ::OBSTACLE)
	{
		m_fSpeed *= -1.f;
	}
}