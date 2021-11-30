#include "Coin.h"
#include "Manager.h"
void CCoin::Initialize(void)
{
	m_bDead = false;
	m_eDir = DIR::UP;
	m_eID = OBJ::ITEM;
	m_fSpeed = 0.5f;
	m_State = STATE::IDLE;
	m_tInfo.fCX = 18;
	m_tInfo.fCY = 32;

	m_SpinTime = GetTickCount(); 
	CBmpMgr::Get_Instance()->Insert_Bmp(COIN_1_BMP,COIN_1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(COIN_2_BMP, COIN_2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(COIN_3_BMP, COIN_3_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(COIN_4_BMP, COIN_4_KEY);
}

int CCoin::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoin::Late_Update(void)
{
}

void CCoin::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC =NULL;

	switch (m_bmpCount)
	{
	case 0:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(COIN_1_KEY);
		if (m_SpinTime + 200.f < GetTickCount())
		{
			++m_bmpCount;
			m_SpinTime = GetTickCount();
		}
		break;
	case 1:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(COIN_2_KEY);
		if (m_SpinTime + 200.f < GetTickCount())
		{
			++m_bmpCount;
			m_SpinTime = GetTickCount();
		}
		break;
	case 2:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(COIN_3_KEY);
		if (m_SpinTime + 200.f < GetTickCount())
		{
			++m_bmpCount;
			m_SpinTime = GetTickCount();
		}
		break;
	case 3:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(COIN_4_KEY);
		if (m_SpinTime + 200.f < GetTickCount())
		{
			m_bmpCount = 0;
			m_SpinTime = GetTickCount();
		}
		break;
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 18, 32, RGB(255, 255, 255));
}

void CCoin::Release(void)
{
}

void CCoin::Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _x, float _y)
{
	if (m_bDead)
		return; 

	switch (_id)
	{
    case OBJ::PLAYER:
		m_bDead = true;
		CDataMgr::Get_Instance()->Add_Coin(1);
        break;
    default:
        break;
	}
}
