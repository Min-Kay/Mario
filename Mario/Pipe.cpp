#include "Pipe.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CPipe::CPipe()
{
}


CPipe::~CPipe()
{
}

void CPipe::Initialize(void)
{
	m_eID = OBJ::OBSTACLE;
	m_eBlockID = BLOCK::PIPE;

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 96.f;
	m_bDead = false;
	m_isInvisible = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(PIPE_PATH, PIPE_KEY);
}

int CPipe::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPipe::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(PIPE_KEY);
	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, 64, 96, RGB(255, 255, 255));
}
