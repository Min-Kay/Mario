#include "framework.h"
#include "Block.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBlock::CBlock() 
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
	m_bDead = false;
	m_isInvisible = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(IRON_BOX_PATH, IRON_BOX_KEY);
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(IRON_BOX_KEY);
}

int CBlock::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;

}


void CBlock::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, BRICK_SIZE_X, BRICK_SIZE_Y, RGB(255, 255, 255));
}


void CBlock::Setup(BLOCK::ID _type, bool _isInvisible)
{
	m_eBlockID = _type;
	m_isInvisible = _isInvisible;
}
