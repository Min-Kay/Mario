#include "Koopa_bullet.h"
#include "Manager.h"

CKoopa_bullet::CKoopa_bullet()
{
}


CKoopa_bullet::~CKoopa_bullet()
{
}

void CKoopa_bullet::Initialize(void)
{
	m_eID = OBJ::BULLET;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_iCount = 0;
	m_bHide = false;
	m_fSpeed = 0.f;
	m_bDead = false;

	m_Walk = false;
	m_WalkTime = GetTickCount();

	m_iCount = 0;

	m_eDir = DIR::RIGHT;
	m_State = STATE::IDLE;

	m_vaild = true;
	m_vaildTime = GetTickCount();
	CBmpMgr::Get_Instance()->Insert_Bmp(KOOPA_DIE_BMP, KOOPA_DIE_KEY);
}

int CKoopa_bullet::Update(void)
{
	if (m_vaild && m_vaildTime + 300.f < GetTickCount())
	{
		m_vaild = false;
		
	}

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

	m_tInfo.fX -= m_fSpeed;

	if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);

	Update_Rect();

	return OBJ_NOEVENT;
}


void CKoopa_bullet::Late_Update(void)
{
	/*if ((0 >= m_tRect.left) || (WINCX <= m_tRect.right))
	m_fSpeed *= -1.f;*/
}

void CKoopa_bullet::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC mMemDC = NULL;
	switch (m_State)
	{
	case STATE::IDLE:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(KOOPA_DIE_KEY);
		break;
	case STATE::DIE:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(KOOPA_DIE_KEY);
		break;
	default:
		break;
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CKoopa_bullet::Release(void)
{
}

void CKoopa_bullet::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (m_vaild)
	{
		return;
	}

	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::UP:
			break;
		case DIR::LEFT:
			m_fSpeed -= 10.f;
			break;
		case DIR::RIGHT:
			m_fSpeed += 10.f;
			break;
		}
	}
		
}
