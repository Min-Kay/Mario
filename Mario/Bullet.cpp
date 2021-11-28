#include "framework.h"
#include "Bullet.h"
#include "Manager.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_eID = OBJ::BULLET;

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;

	m_fSpeed = 3.f;

	m_iCount = 0;
	m_bJump = true;
	m_fTime = 0.f;
	m_fJumpPower = 40.f;
	m_fJumpY = m_tInfo.fY;

	m_bDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(FIREBALL_1_BMP, FIREBALL_1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FIREBALL_2_BMP, FIREBALL_2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(FIREBALL_3_BMP, FIREBALL_3_KEY);
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIR::LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case DIR::RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	}

	Jumping();

	Update_Rect();

	return OBJ_NOEVENT;

}

void CBullet::Late_Update(void)
{
	if (Screen_Out_Check())
		Set_Dead(true);
}

void CBullet::Render(HDC hDC)
{
	HDC hMemDC = NULL;
	switch (m_AnimNum)
	{
	case 0:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FIREBALL_1_KEY);
		++m_AnimNum;
		break;
	case 1:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FIREBALL_2_KEY);
		++m_AnimNum;
		break;
	case 2:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FIREBALL_3_KEY);
		m_AnimNum = 0;
		break;
	}
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, 16, 16, RGB(255, 255, 255));
}

void CBullet::Release(void)
{

}

void CBullet::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (_eID == OBJ::MONSTER)
	{
		switch (_eDIR)
		{
		default:
			m_bDead = true;
			break;
		}
	}
}

void CBullet::Jumping(void)
{
	if (m_bDead)
		return; 

	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.2f;

		if (bLineCol && (fY + 2 < m_tInfo.fY + (m_tInfo.fCY * 0.5f)))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_iCount++;
			if (m_iCount > 2)
				m_bDead = true;
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		m_fJumpY = m_tInfo.fY;
		m_bJump = true;
	}
}