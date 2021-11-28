#include "framework.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Manager.h"

CPlayer::CPlayer()
	:m_fall(0)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Key_Input(void)
{
	if (m_bDead)
		return;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
		m_eDir = DIR::LEFT;
		m_State = STATE::RUN;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
		m_eDir = DIR::RIGHT;
		m_State = STATE::RUN;
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
		float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		CObjPoolMgr::Get_Instance()->Spawn_Bullet(BULLET::BULLET, m_tInfo.fX + ScrollX, m_tInfo.fY, m_eDir);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		m_bDead = true;
	}
}

void CPlayer::Jumping(void)
{
	if (m_bDead)
		return; 

	float		fY = 0.f;

	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (true == m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.2f;
		m_State = STATE::JUMP;
		if (bLineCol && fY + 10 < m_tInfo.fY + (m_tInfo.fCY * 0.5f))
		{
			m_bJump = false;
			m_State = STATE::IDLE;
			m_fTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		}
		
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		m_fall = 0;
	}
	else 
	{
		m_State = STATE::JUMP;
		m_tInfo.fY += m_fall;
		++m_fall;
	}
}

void CPlayer::Show_Dying_Anim()
{
	if (m_bDead)
	{
		m_State = STATE::DIE;
		m_fall = 15.0f; 
		if (m_DeadTime + 1000.f > GetTickCount())
		{
			
		}
		else if (m_total < 100.f)
		{
			m_tInfo.fY -= 4.5f;
			m_total += 4.5f;
		}
		else
		{
			m_tInfo.fY += m_fall;
		}
	}
	else
	{
		m_DeadTime = GetTickCount(); 
		m_total = 0;
	}
}

void CPlayer::Initialize(void)
{
	m_eID = OBJ::PLAYER;
	m_eDir = DIR::RIGHT;

	m_tInfo.fX = PLAYER_POS_X;
	m_tInfo.fY = PLAYER_POS_Y;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 5.f;

	m_fTime = 0.f;
	m_bJump = false;
	m_bDead = false; 
	m_fJumpPower = 50.f;
	m_fJumpY = 0.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_L_BMP, PLAYER_L_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_R_BMP, PLAYER_R_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_L_RUN1_BMP, PLAYER_L_RUN1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_L_RUN2_BMP, PLAYER_L_RUN2_KEY);

	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_R_RUN1_BMP, PLAYER_R_RUN1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_R_RUN2_BMP, PLAYER_R_RUN2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_L_JUMP_BMP, PLAYER_L_JUMP_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_R_JUMP_BMP, PLAYER_R_JUMP_KEY);

	CBmpMgr::Get_Instance()->Insert_Bmp(PLAYER_DIE_BMP, PLAYER_DIE_KEY);

}

int CPlayer::Update(void)
{
	Key_Input();
	Jumping();
	Show_Dying_Anim();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC	hMemDC;
	switch (m_State)
	{
	case STATE::IDLE:
		if(m_eDir == DIR::LEFT)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_KEY);
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_KEY);
		break; 
	case STATE::RUN:
		if (m_eDir == DIR::LEFT)
			hMemDC = m_walk ? CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_RUN1_KEY) : CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_RUN2_KEY);
		else
			hMemDC = m_walk ? CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_RUN1_KEY) : CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_RUN2_KEY);
		
		m_State = STATE::IDLE;
		m_walk = !m_walk;
		break;
	case STATE::JUMP:
		if (m_eDir == DIR::LEFT)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_JUMP_KEY);
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_JUMP_KEY);
		break;
	case STATE::DIE:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_DIE_KEY);
		break;
	default:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_KEY);
		break;
	}

	if (m_State == STATE::DIE)
	{
		GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, 30, 28, RGB(255, 255, 255));
	}
	else 
		GdiTransparentBlt(hDC,int(m_tRect.left + ScrollX),int(m_tRect.top),(int)m_tInfo.fCX,(int)m_tInfo.fCY,hMemDC,0,0,32,32,RGB(255, 255, 255));
}

void CPlayer::Release(void)
{
}

void CPlayer::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (m_bDead)
		return;

	if (_eID == OBJ::MONSTER)
	{
		switch (_eDIR)
		{
		case DIR::DOWN:
			m_bJump = true;
			m_fJumpY = m_tInfo.fY;
			m_fTime = 0.f;
			break;
		default:
			m_bDead = true;
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
