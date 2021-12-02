#include "Flower.h"
#include"Manager.h"


CFlower::CFlower()
{
}


CFlower::~CFlower()
{
}

void CFlower::Initialize(void)
{
	m_eID = OBJ::ITEM;
	m_itemId = ITEM::FLOWER;
	m_bDead = false;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_State = STATE::IDLE;
	m_fSpeed = 1.f;
	m_fGravity = 0.5f; // 중력은 모두가 가지고 있어야하는거 static 만들면 좋을것
	m_IsObjCol = false;
	m_isAni = true;
	m_AnimTimer = GetTickCount();
	m_Count = 0;

	m_Vaild = true;
	m_VaildTime = GetTickCount();
	CBmpMgr::Get_Instance()->Insert_Bmp(FLOWER_ITEM_1_BMP,FLOWER_ITEM_1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FLOWER_ITEM_2_BMP, FLOWER_ITEM_2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FLOWER_ITEM_3_BMP, FLOWER_ITEM_3_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FLOWER_ITEM_4_BMP, FLOWER_ITEM_4_KEY);

}

int CFlower::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_isAni)
		StartAnimation();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlower::Late_Update(void)
{
	if (m_Vaild && m_VaildTime + 200.f < GetTickCount())
	{
		m_Vaild = false;
	}
}

void CFlower::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC = NULL;

	switch (m_Count)
	{
	case 0:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(FLOWER_ITEM_1_KEY);
		if (m_AnimTimer + 100.f < GetTickCount())
		{
			m_AnimTimer = GetTickCount(); 
			++m_Count;
		}
		break;
	case 1:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(FLOWER_ITEM_2_KEY);
		if (m_AnimTimer + 100.f < GetTickCount())
		{
			m_AnimTimer = GetTickCount();
			++m_Count;
		}
		break;
	case 2:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(FLOWER_ITEM_3_KEY);
		if (m_AnimTimer + 100.f < GetTickCount())
		{
			m_AnimTimer = GetTickCount();
			++m_Count;
		}
		break;
	case 3:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(FLOWER_ITEM_4_KEY);
		if (m_AnimTimer + 100.f < GetTickCount())
		{
			m_AnimTimer = GetTickCount();
			m_Count = 0;
		}
		break;
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CFlower::Release(void)
{
}

void CFlower::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_OriginY = _fY;
}

void CFlower::Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth, float _fHeight)
{
	if (m_Vaild || m_bDead)
		return;

	if (_id == OBJ::ID::PLAYER)
	{
		m_bDead = true;
	}
	
	if (_id == OBJ::ID::OBSTACLE)
	{
		if (m_isAni)
			return;

		else
			m_tInfo.fY -= _fHeight;
	}
}

void CFlower::StartAnimation(void)
{
	float fSpeed = 0.5f;
	float fMaxDis = m_OriginY - m_tInfo.fCY + 5.f;

	if (m_tInfo.fY <= fMaxDis)
		m_isAni = false;

	else
		m_tInfo.fY -= m_fSpeed;
}

void CFlower::Gravity(void)
{
	m_Force += m_fGravity;
	m_tInfo.fY += m_Force;
}
