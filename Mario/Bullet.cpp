#include "framework.h"
#include "Bullet.h"
#include "Manager.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;

	m_fSpeed = 13.f;

	m_eID = OBJ::BULLET;

	CBmpMgr::Get_Instance()->Insert_Bmp(FIREBALL_1_BMP, FIREBALL_1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FIREBALL_2_BMP, FIREBALL_2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FIREBALL_3_BMP, FIREBALL_3_KEY);
}

int CBullet::Update(void)
{	
	if (true == m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIR::LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case DIR::RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;

}

void CBullet::Late_Update(void)
{
	if (0			>= m_tRect.left		||
		WINCX		<= m_tRect.right	||
		0			>= m_tRect.top		||
		WINCY		 <= m_tRect.bottom)
	{ 
		m_bDead = true;
	}		
}

void CBullet::Render(HDC hDC)
{
	HDC hMemDC = NULL;
	switch (m_AnimNum)
	{
	case 0:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FIREBALL_1_KEY);
		++m_AnimNum;
		break;
	case 1:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FIREBALL_2_KEY);
		++m_AnimNum;
		break; 
	case 2:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FIREBALL_3_KEY);
		m_AnimNum = 0;
		break;
	}
	GdiTransparentBlt(hDC, int(m_tRect.left), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, 16, 16, RGB(255, 255, 255));
}

void CBullet::Release(void)
{
	
}

void CBullet::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (_eID == OBJ::MONSTER)
	{
		switch (_eDIR)
		{
		default:
			m_bDead = true;
			break;
		}
	}
}