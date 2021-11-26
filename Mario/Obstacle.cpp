#include "framework.h"
#include "Obstacle.h"
#include "ScrollMgr.h"

CObstacle::CObstacle()
{
}


CObstacle::~CObstacle()
{
}

void CObstacle::Initialize(void)
{
	m_eID = OBJ::OBSTACLE;

	m_tInfo.fX = 700.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CObstacle::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;

}

void CObstacle::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CObstacle::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right + ScrollX, m_tRect.bottom);
}

void CObstacle::Release(void)
{

}

void CObstacle::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{

	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::UP:
		{
		//m_tRect.top 
		}
		break;
		case DIR::DOWN:
			m_bDead = true;
			break;

		}
	}
}