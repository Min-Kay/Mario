#include "Koopa.h"
#include "Include.h"
#include "Manager.h"
#include "AbstractFactory.h"
#include "Koopa_bullet.h"

CKoopa::CKoopa()
{
}


CKoopa::~CKoopa()
{

}

void CKoopa::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_iCount = 0;
	m_bHide = false;
	m_fSpeed = 1.f;
	m_bDead = false;

	m_eDir = DIR::RIGHT;
	m_State = STATE::IDLE;

	CBmpMgr::Get_Instance()->Insert_Bmp(KOOPA_L_BMP, KOOPA_L_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(KOOPA_R_BMP, KOOPA_R_KEY);
}

int CKoopa::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if(m_bMove)
	{
		float		fY = 0.f;
		bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

		m_tInfo.fX -= m_fSpeed;

		if (bLineCol)
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		else
			m_tInfo.fY += FALL_DOWN;
	}
	else
		Check_StartMove();

	Update_Rect();

	return OBJ_NOEVENT;
}


void CKoopa::Late_Update(void)
{
	/*if ((0 >= m_tRect.left) || (WINCX <= m_tRect.right))
		m_fSpeed *= -1.f;*/
}

void CKoopa::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	
	HDC mMemDC = NULL;
	switch (m_State)
	{
	case STATE::IDLE:
		if (m_Walk)
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(KOOPA_L_KEY);
			if (m_WalkTime + 100.f < GetTickCount())
			{
				m_WalkTime = GetTickCount();
				m_Walk = !m_Walk;
			}
		}
		else
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(KOOPA_R_KEY);
			if (m_WalkTime + 100.f < GetTickCount())
			{
				m_WalkTime = GetTickCount();
				m_Walk = !m_Walk;
			}
		}
		break;
	case STATE::DIE:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(KOOPA_R_KEY);
		break;
	default:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(KOOPA_L_KEY);
		break;
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CKoopa::Release(void)
{
}

void CKoopa::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::UP:
			m_bDead = true;
			m_State = STATE::DIE;
			CObjPoolMgr::Get_Instance()->Spawn_Bullet(BULLET::KOOPA_BULLET, m_tInfo.fX, m_tInfo.fY, DIR::LEFT);
			break;
		}
	
	}
	else if (_eID == OBJ::BULLET)
	{
		switch (_eDIR)
		{
		default:
			m_bDead = true;
			break;
		}
	}
	else if (_eID == OBJ::OBSTACLE)
	{
		switch (_eDIR)
		{
		case DIR::RIGHT:
		case DIR::LEFT:
			m_fSpeed *= -1;
			break;
		}
	}
}
