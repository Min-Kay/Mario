#include "BreakableBlock.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CBreakableBlock::Initialize(void)
{
	m_eID = OBJ::OBSTACLE;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_isAni = false;
	m_isReverse = false;
	m_isInvisible = false;
	CBmpMgr::Get_Instance()->Insert_Bmp(IMAGE_BRICK_PATH, IMAGE_BRICK_KEY);
}

int CBreakableBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	UpdateAnimation();
	
	return OBJ_NOEVENT;
}

void CBreakableBlock::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC = CBmpMgr::Get_Instance()->Find_Image(IMAGE_BRICK_KEY);
	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, BRICK_SIZE_X, BRICK_SIZE_Y, RGB(255, 255, 255));
}

void CBreakableBlock::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (m_bDead)
		return;

	if (_eID == OBJ::PLAYER)
	{
		if (_eDIR == DIR::DOWN)
		{
			PlayAction(true);
		}
	}
}

void CBreakableBlock::Set_Pos(float _fX, float _fY)
{
	CObj::Set_Pos(_fX, _fY);
	m_originPosX = m_tInfo.fX;
	m_originPosY = m_tInfo.fY;
}

void CBreakableBlock::StartAnimation()
{
	m_isAni = true;
	m_isReverse = false;
}

void CBreakableBlock::UpdateAnimation()
{
	if (!m_isAni)
		return;

	float aniSpeed = 2.f;
	float moveDis = 10.f;

	m_tInfo.fY -= m_isReverse ? -aniSpeed : aniSpeed;

	if (!m_isReverse && m_tInfo.fY < m_originPosY - moveDis)
		m_isReverse = true;

	if (m_isReverse && m_tInfo.fY >= m_originPosY)
	{
		m_tInfo.fY = m_originPosY;
		m_isAni = false;
		DestoryBlock();
	}
}

void CBreakableBlock::DestoryBlock()
{
	m_bDead = true;
}

void CBreakableBlock::PlayAction(bool _isDestory)
{
	StartAnimation();
}
