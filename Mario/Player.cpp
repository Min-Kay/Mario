#include "framework.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Manager.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Key_Input(void)
{
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ::BULLET , CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR::LEFT));
		}
		m_tInfo.fX -= m_fSpeed;
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		if (!m_bJump)
		{
			m_fJumpY = m_tInfo.fY;
			m_bJump = true;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ::BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}



void CPlayer::Jumping(void)
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

void CPlayer::Initialize(void)
{
	m_eID = OBJ::PLAYER;

	m_tInfo.fX = PLAYER_POS_X;
	m_tInfo.fY = PLAYER_POS_Y;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;

	m_fTime = 0.f;
	m_bJump = false;
	m_fJumpPower = 50.f;
	m_fJumpY = 0.f;
}

int CPlayer::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Key_Input();
	Jumping();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_tInfo.fY >= WINCY)
	{
		CDataMgr::Get_Instance()->Add_Life(-1);
	}
}

void CPlayer::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	
	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right+ ScrollX, m_tRect.bottom);
}

void CPlayer::Release(void)
{
	
}

void CPlayer::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (_eID == OBJ::MONSTER)
	{
		switch (_eDIR)
		{
		case DIR::DOWN:
			// Á¡¼ö È¹µæ
			// Á¡ÇÁ È¿°ú
			m_bJump = true;
			m_fJumpY = m_tInfo.fY;
			m_fTime = 0.f;
			break;
		}
	}
	if (_eID == OBJ::OBSTACLE)
	{
		switch (_eDIR)
		{
		case DIR::DOWN:
			m_fJumpY = m_tInfo.fY;
			break;

		}
	}
}
