#include "framework.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 13.f;
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
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
	
}
