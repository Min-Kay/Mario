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
	m_bRun = false;
	Above_Block = false;
	Jump_On = false;
	is_Not_Down = false;
	is_Collision = false;

	isVaild = true;
	m_VaildTime = GetTickCount();
	CoolTime = 3000.f;

	m_JumpTime = GetTickCount();
	init_JumpTime = false;

	Cal_MaxJumpTime(&m_fMaxJumpTime);

	m_fJumpPower = 50.f;
	m_fJumpY = 0.f;

	m_fRunSpeed = 6.5f;
	m_WalkAnim = 100.f;

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
	Update_Collision_Rect();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Set_Vaild();
	Show_Dying_Anim();
}

void CPlayer::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC	hMemDC = NULL;
	switch (m_State)
	{
	case STATE::IDLE:
		if (m_eDir == DIR::LEFT)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_KEY);
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_KEY);
		break;
	case STATE::RUN:
		if (m_eDir == DIR::LEFT)
		{
			if (m_walk)
			{
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_RUN1_KEY);

				if (m_WalkTime + m_WalkAnim < GetTickCount())
				{
					m_walk = !m_walk;
					m_WalkTime = GetTickCount();
				}
			}
			else if (!m_walk)
			{
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_L_RUN2_KEY);
				if (m_WalkTime + m_WalkAnim < GetTickCount())
				{
					m_walk = !m_walk;
					m_WalkTime = GetTickCount();
				}
			}
		}
		else
		{
			if (m_walk)
			{
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_RUN1_KEY);

				if (m_WalkTime + m_WalkAnim < GetTickCount())
				{
					m_walk = !m_walk;
					m_WalkTime = GetTickCount();
				}
			}
			else if (!m_walk)
			{
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(PLAYER_R_RUN2_KEY);
				if (m_WalkTime + m_WalkAnim < GetTickCount())
				{
					m_walk = !m_walk;
					m_WalkTime = GetTickCount();
				}
			}
		}
		m_State = STATE::IDLE;
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
		GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CPlayer::Release(void)
{
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

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RUN))
	{
		if (!m_bRun)
		{
			m_bRun = true;
			m_WalkAnim *= 0.5f;
			m_fSpeed += m_fRunSpeed;
		}
	}
	else
	{
		if (m_bRun)
		{
			m_bRun = false;
			m_WalkAnim *= 2;
			m_fSpeed -= m_fRunSpeed;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ATTACK))
	{
		CObjPoolMgr::Get_Instance()->Spawn_Bullet(BULLET::BULLET, m_tInfo.fX, m_tInfo.fY, m_eDir);
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
	
	if (m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.2f;
		m_State = STATE::JUMP;
		
		if (!init_JumpTime)
		{
			m_JumpTime = GetTickCount();
			init_JumpTime = true;
		}

		if (is_Collision && !Above_Block && !is_Not_Down)
		{
			is_Collision = false;
			init_JumpTime = false;
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY += FALL_DOWN * 0.5f;
		}
		else if (Above_Block && m_JumpTime + 50.f < GetTickCount() && is_Not_Down)
		{
			init_JumpTime = false;
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = m_CollisionY - m_tInfo.fCY * 0.5f;
		}
		else if (bLineCol && fY + 10 < m_tInfo.fY + (m_tInfo.fCY * 0.5f))
		{
			m_bJump = false;
			m_State = STATE::IDLE;
			m_fTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		}
	}
	else if (Above_Block && !m_bJump && is_Not_Down)
	{
		if (m_State == STATE::JUMP)
			m_State = STATE::IDLE;
		m_tInfo.fY = m_CollisionY - m_tInfo.fCY * 0.5f;
	}
	else if (bLineCol && m_tInfo.fY < fY - (m_tInfo.fCY * 1.f))
	{
		m_State = STATE::JUMP;
		m_tInfo.fY += FALL_DOWN * 0.5f;
	}
	else if (bLineCol && m_tInfo.fY >= fY - (m_tInfo.fCY * 0.5f))
	{
		if (m_State == STATE::JUMP)
			m_State = STATE::IDLE;
		m_bJump = false;
		m_fTime = 0.f;
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
	}
	else if (bLineCol)
	{
		if (m_State == STATE::JUMP)
			m_State = STATE::IDLE;
		m_bJump = false;
		m_fTime = 0.f;
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
	}
	
}

void CPlayer::Show_Dying_Anim()
{
	if (m_bDead)
	{
		m_State = STATE::DIE;
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
			m_tInfo.fY += FALL_DOWN;
		}
	}
	else
	{
		m_DeadTime = GetTickCount(); 
		m_total = 0;
	}
}

void CPlayer::Set_Vaild()
{
	if (isVaild && m_VaildTime + CoolTime < GetTickCount())
	{
		m_VaildTime = GetTickCount();
		isVaild = false;
	}
}

void CPlayer::Update_Collision_Rect()
{
	On_Collision_Rect.left = m_tInfo.fX - m_tInfo.fCX * 0.5f;
	On_Collision_Rect.right = m_tInfo.fX + m_tInfo.fCX * 0.5f;
	On_Collision_Rect.top = m_tInfo.fY + m_tInfo.fCY * 0.5f;
	On_Collision_Rect.bottom = m_tInfo.fY + m_tInfo.fCY * 0.55f;
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
			isVaild = true;
			m_VaildTime = GetTickCount();
			CoolTime = 500.f;
			break;
		default:
			if (isVaild)
				break;
			m_bDead = true;
			isVaild = true;
			m_VaildTime = GetTickCount();
			CoolTime = 3000.f;
			break;
		}
	}
	else if (_eID == OBJ::OBSTACLE)
	{
		is_Collision = true; 
		switch (_eDIR)
		{
		case DIR::UP:
			is_Not_Down = false;
			break;
		default:
			is_Not_Down = true;
			break;
		}
	}
}


void CPlayer::Cal_MaxJumpTime(float* _fMaxJumpTime)
{
	float fJumpY = 0.f;
	float fJumpTime = 0.f;

	while (fJumpY >= 0)
	{
		fJumpY = m_fJumpPower * fJumpTime - 9.8f * fJumpTime * fJumpTime * 0.5f;
		fJumpTime += 0.2f;
	}

	*_fMaxJumpTime = fJumpTime;
}