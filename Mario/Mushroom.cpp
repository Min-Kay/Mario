#include "Mushroom.h"
#include "Manager.h"


CMushroom::CMushroom()
{
}


CMushroom::~CMushroom()
{
}

void CMushroom::Initialize(void)
{
	m_eID = OBJ::ITEM;
	m_itemId = ITEM::MUSHROOM;

	m_bDead = false;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_fSpeed = 1.f;
	m_fGravity = 0.5f; // 중력은 모두가 가지고 있어야하는거 static 만들면 좋을것
	m_State = STATE::IDLE;
	m_IsObjCol = false;
	m_isAni = true;
	
	m_Vaild = true;
	m_VaildTime = GetTickCount();

	CBmpMgr::Get_Instance()->Insert_Bmp(MUSHROOM_BMP,MUSHROOM_KEY);
	
}

int CMushroom::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if(m_isAni)
	StartAnimation();
	
	else
	{
		Moving();
		Gravity();
	}
	Update_Rect();
	
	return OBJ_NOEVENT;
}

void CMushroom::Late_Update(void)
{
	if (m_Vaild && m_VaildTime + 200.f < GetTickCount())
	{
		m_Vaild = false;
	}
}

void CMushroom::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC = CBmpMgr::Get_Instance()->Find_Image(MUSHROOM_KEY);
	Update_Rect();
	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CMushroom::Release(void)
{
}

void CMushroom::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_OriginY = _fY;
}

void CMushroom::Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth, float _fHeight)
{
	if (m_Vaild)
		return;

	if (_id == OBJ::ID::OBSTACLE)
	{
		if (m_isAni)
			return;

		switch (_dir)
		{
		case DIR::DIR::DOWN:
			m_fY = _fHeight;
			break;

		case DIR::DIR::UP:
			m_fY = -_fHeight;
			break;
		}
		m_IsObjCol = true;
	}

	if (_id == OBJ::ID::PLAYER)
	{
		m_bDead = true;
	}
}

void CMushroom::Gravity(void)
{
	m_Force += m_fGravity;
	m_tInfo.fY += m_Force;
}

void CMushroom::Moving(void)
{
	m_tInfo.fX += m_fSpeed;

	// 오브젝트 충돌시 리턴
	if (m_IsObjCol)
	{
		m_Force = 0.f;
		m_IsObjCol = false;
		OnTheBlock(m_fY);
		return;
	}
	//
	float bottomPos = m_tInfo.fY + (m_tInfo.fCY) * 0.5;
	//라인 충돌 구현부
	float fY = 0.f;
	bool isCollision =  CLineMgr::Get_Instance()->Collision_Line_NoDistance(m_tInfo.fX, m_tInfo.fY,&fY);
	if (isCollision && fY < bottomPos)
	{
		m_Force = 0.f;
		m_tInfo.fY = fY - (m_tInfo.fCY) * 0.5;
	}
}

void CMushroom::StartAnimation(void)
{
	float fSpeed = 0.5f;
	float fMaxDis = m_OriginY - m_tInfo.fCY + 5.f;
	
	if (m_tInfo.fY <= fMaxDis)
		m_isAni = false;
	
	else 
	m_tInfo.fY -= m_fSpeed;
}

void CMushroom::OnTheBlock(float _fY)
{
	m_tInfo.fY -= _fY;
}
