#include "framework.h"
#include "Obstacle_Item.h"

CObstacle_Item::CObstacle_Item()
{
}


CObstacle_Item::~CObstacle_Item()
{
}

void CObstacle_Item::Initialize(void)
{
	m_eID = OBJ::OBSTACLE;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CObstacle_Item::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;

}

void CObstacle_Item::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CObstacle_Item::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObstacle_Item::Release(void)
{

}

void CObstacle_Item::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{

	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::UP:
			break;
		case DIR::DOWN:
			m_bDead = true;
			break;
		}
	}
}