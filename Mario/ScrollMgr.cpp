#include "framework.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
	Release();
}

void CScrollMgr::Update(void)
{

}

void CScrollMgr::Late_Update(void)
{
}

void CScrollMgr::Release(void)
{
	Init_ScrollX(0);
}

