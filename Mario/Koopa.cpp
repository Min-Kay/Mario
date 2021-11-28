#include "Koopa.h"
#include "Include.h"
#include "Manager.h"


CKoopa::CKoopa()
{
}


CKoopa::~CKoopa()
{
}

void CKoopa::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_iCount = 0;
	m_bHide = false;
	m_fSpeed = 1.f;
	m_bDead = false;

}

int CKoopa::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	m_tInfo.fX -= m_fSpeed;

	if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);

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
	
	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right + ScrollX, m_tRect.bottom);
}

void CKoopa::Release(void)
{
}

void CKoopa::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (_eID == OBJ::PLAYER)
	{
		if (0 == m_iCount)
		{
			switch (_eDIR)
			{
			case DIR::UP:
				m_bHide = true;
				m_fSpeed = 0.f;
				m_tInfo.fCX -= 5;
				m_tInfo.fCY -= 5;
				++m_iCount;
				break;
			}
		}
		if (1 == m_iCount)
		{
			if (_eID == OBJ::MONSTER)
			{
				if (0 == m_iCount)
				{
					switch (_eDIR)
					{
					case DIR::LEFT:
						break;
					case DIR::RIGHT:
						break;
					}
				}
			}	
			switch (_eDIR)
			{
			case DIR::UP:
				m_fSpeed += 10.f;
				m_tInfo.fCX -= 0.0001;
				m_tInfo.fCY -= 0.0001;
				m_bHide = false;
				++m_iCount;
				break;
			case DIR::LEFT:
				m_fSpeed -= 10.f;
				++m_iCount;
				break;
			case DIR::RIGHT:
				m_fSpeed += 10.f;
				++m_iCount;
				break;
			}
		}
		if (2 <= m_iCount)
		{
			switch (_eDIR)
			{
			case DIR::UP:
				m_bHide = true;
				m_fSpeed = 0.f;
				m_tInfo.fCX -= 0.0001;
				m_tInfo.fCY -= 0.0001;
				m_iCount = 1;
				break;
			}
		}
			
	}
	
	if (_eID == OBJ::BULLET)
	{
		switch (_eDIR)
		{
		default:
			m_bDead = true;
			break;
		}
	}

	if (_eID == OBJ::OBSTACLE)
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
