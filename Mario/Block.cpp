#include "framework.h"
#include "Block.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CBlock::CBlock() 
	: m_isAni(false)
{
}

CBlock::~CBlock()
{
}
void CBlock::Initialize(void)
{
	m_eID = OBJ::OBSTACLE;
	m_eBlockID = BLOCK::DEFAULT;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
}

int CBlock::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;

}

void CBlock::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CBlock::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right + ScrollX, m_tRect.bottom);
}

void CBlock::Release(void)
{

}

void CBlock::Set_Pos(float _fX, float _fY)
{
	CObj::Set_Pos(_fX , _fY);
	m_originPosX = m_tInfo.fX;
	m_originPosY = m_tInfo.fY;
}

void CBlock::Setup(BLOCK::ID _type, bool _isInvisible)
{
}

void CBlock::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
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

void CBlock::Gravity()
{
	m_tInfo.fY -= m_iForce;
	m_iForce -= m_iGravity;

}

void CBlock::StartAnimation()
{
	m_isAni = true;
}

void CBlock::UpdateAnimation()
{

}
