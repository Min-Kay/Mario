#include "MonsterFlower.h"
#include "Manager.h"


CMonsterFlower::CMonsterFlower()
{
}


CMonsterFlower::~CMonsterFlower()
{
}
void CMonsterFlower::Initialize(void)
{
	m_eID = OBJ::MONSTER;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_eDir = DIR::RIGHT;
	m_State = STATE::IDLE;

	CBmpMgr::Get_Instance()->Insert_Bmp(MONSTER_FLOWER_L_BMP, MONSTER_FLOWER_L_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(MONSTER_FLOWER_R_BMP, MONSTER_FLOWER_R_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(MONSTER_FLOWER_DIE_BMP, MONSTER_FLOWER_DIE_KEY);
}


int CMonsterFlower::Update(void)
{
	if (m_bDead)
	{
		m_tInfo.fY += FALL_DOWN;
		if (m_tInfo.fY >= WINCY)
		{
			m_State = STATE::DIE;
			return OBJ_DEAD;
		}
		Update_Rect();
		return OBJ_NOEVENT;
	}

	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);


	if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);

	Update_Rect();

	return OBJ_NOEVENT;
}


void CMonsterFlower::Late_Update(void)
{

}

void CMonsterFlower::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC mMemDC = NULL;
	switch (m_State)
	{
	case STATE::IDLE:
		if (m_Walk)
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(MONSTER_FLOWER_L_KEY);
			if (m_WalkTime + 100.f < GetTickCount())
			{
				m_WalkTime = GetTickCount();
				m_Walk = !m_Walk;
			}
		}
		else
		{
			mMemDC = CBmpMgr::Get_Instance()->Find_Image(MONSTER_FLOWER_R_KEY);
			if (m_WalkTime + 100.f < GetTickCount())
			{
				m_WalkTime = GetTickCount();
				m_Walk = !m_Walk;
			}
		}
		break;
	case STATE::DIE:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(MONSTER_FLOWER_DIE_KEY);
		break;
	default:
		mMemDC = CBmpMgr::Get_Instance()->Find_Image(MONSTER_FLOWER_L_KEY);
		break;
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));
}

void CMonsterFlower::Release(void)
{

}
void CMonsterFlower::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
	if (m_bDead)
		return;

	
}
