#include "framework.h"
#include "Chicken.h"
#include "Manager.h"

CChicken::CChicken()
{
}


CChicken::~CChicken()
{
}
void CChicken::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fX = 600.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 2.f;

	m_bDead = false;

	m_fTime = 10.f;
	m_bJump = false;
	m_fJumpPower = 15.f;
	m_fJumpY = 0.f;

	m_eDir = DIR::RIGHT;
	m_State = STATE::IDLE;

	CBmpMgr::Get_Instance()->Insert_Bmp(CHICKEN_L1_BMP, CHICKEN_L1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CHICKEN_L2_BMP, CHICKEN_L2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CHICKEN_R1_BMP, CHICKEN_R1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CHICKEN_R2_BMP, CHICKEN_R2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CHICKEN_DIE_BMP, CHICKEN_DIE_KEY);
}


int CChicken::Update(void)
{
	DWORD m_dwTime = 0;

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

void CChicken::Jumping(void)
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

void CChicken::Late_Update(void)
{
	if ((0 >= m_tRect.left) || (WINCX  <= m_tRect.right))
	m_fSpeed *= -1.f;

	if (WINCX <= m_tRect.right)
		m_eDir = DIR::LEFT;

	if (Screen_Out_Check())
		Set_Dead(true);
}

void CChicken::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC = NULL;

		if (m_Walk)
		{
			if (m_eDir == DIR::LEFT)
			{
				mMemDC = CBmpMgr::Get_Instance()->Find_Image(CHICKEN_L1_KEY);
				if (m_WalkTime + 100.f < GetTickCount())
				{
					m_WalkTime = GetTickCount();
					m_Walk = !m_Walk;
				}
			}
				if (m_eDir == DIR::RIGHT)
				{
					mMemDC = CBmpMgr::Get_Instance()->Find_Image(CHICKEN_R1_KEY);
					if (m_WalkTime + 100.f < GetTickCount())
					{
						m_WalkTime = GetTickCount();
						m_Walk = !m_Walk;
					}
				}
		}
		else 
		{
			if (DIR::LEFT)
			{
				mMemDC = CBmpMgr::Get_Instance()->Find_Image(CHICKEN_L2_KEY);
				if (m_WalkTime + 100.f < GetTickCount())
				{
					m_WalkTime = GetTickCount();
					m_Walk = !m_Walk;
				}
			}

			if (DIR::RIGHT)
			{
				mMemDC = CBmpMgr::Get_Instance()->Find_Image(CHICKEN_R2_KEY);
				if (m_WalkTime + 100.f < GetTickCount())
				{
					m_WalkTime = GetTickCount();
					m_Walk = !m_Walk;
				}
			}
		}
		
		if(m_bDead)	
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(CHICKEN_DIE_KEY);
		}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CChicken::Release(void)
{

}
void CChicken::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
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