#include "ItemBlock.h"
#include "ScrollMgr.h"
#include "Manager.h"
#include "AbstractFactory.h"

CItemBlock::CItemBlock()
	: m_isEmpty(false)
	, m_isReverse(false)
	, m_isAni(false)
	, m_curSpriteImageIdx(0)
	, m_OldTickCount(0)

{
}


CItemBlock::~CItemBlock()
{

}
void CItemBlock::Set_Pos(float _fX, float _fY)
{
	CObj::Set_Pos(_fX , _fY);
	m_originPosX = m_tInfo.fX;
	m_originPosY = m_tInfo.fY;
}

void CItemBlock::Initialize(void)
{
	m_eID = OBJ::OBSTACLE;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_isEmpty = false; 
	m_AniTickDelay = 100.f; //높을수록 느려짐
	Setup(BLOCK::ITEM, false);
}

int CItemBlock::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	UpdateAnimation();
	UpdateSpriteAnimation();

	return OBJ_NOEVENT;
}

void CItemBlock::Late_Update(void)
{

}

void CItemBlock::Render(HDC hDC)
{
	if (m_isInvisible)
		return;
	HDC	hMemDC = NULL;
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_isEmpty)
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(IMAGE_QUE_BOX_DIE_KEY);
	else
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_SpriteImageKeys[m_curSpriteImageIdx]);
	}

	GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0, BRICK_SIZE_X, BRICK_SIZE_Y, RGB(255, 255, 255));
}

void CItemBlock::Release(void)
{
}

void CItemBlock::Setup(BLOCK::ID _type, bool _isInvisible)
{
	m_eBlockID = _type;
	m_isInvisible = _isInvisible;

	CBmpMgr::Get_Instance()->Insert_Bmp(IMAGE_QUE_BOX_1_PATH, IMAGE_QUE_BOX_1_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(IMAGE_QUE_BOX_2_PATH, IMAGE_QUE_BOX_2_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(IMAGE_QUE_BOX_3_PATH, IMAGE_QUE_BOX_3_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(IMAGE_QUE_BOX_DIE_PATH, IMAGE_QUE_BOX_DIE_KEY);

	m_SpriteImageKeys[0] = (TCHAR*)IMAGE_QUE_BOX_1_KEY;
	m_SpriteImageKeys[1] = (TCHAR*)IMAGE_QUE_BOX_2_KEY;
	m_SpriteImageKeys[2] = (TCHAR*)IMAGE_QUE_BOX_3_KEY;
	m_SpriteImageKeys[3] = (TCHAR*)IMAGE_QUE_BOX_2_KEY;
	m_SpriteImageKeys[4] = (TCHAR*)IMAGE_QUE_BOX_1_KEY;
	m_isSpriteAni = true;

}

void CItemBlock::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{	
	if (_eID == OBJ::PLAYER)
	{
		switch (_eDIR)
		{
		case DIR::DOWN:
			PlayAction(true);
			break;
		}
	}
}

void CItemBlock::StartAnimation()
{
	m_isAni = true;
	m_isReverse = false;
}

void CItemBlock::UpdateAnimation()
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
	}
}

void CItemBlock::DestoryBlock()
{
	m_bDead = true;
}

void CItemBlock::UpdateSpriteAnimation()
{
	if (!m_isSpriteAni)
		return;

	if (m_OldTickCount + m_AniTickDelay < GetTickCount())
	{
		if (m_curSpriteImageIdx >= 4)
			m_curSpriteImageIdx = 0;
		else
			++m_curSpriteImageIdx;

		m_OldTickCount = GetTickCount();
	}
}

void CItemBlock::PlayAction(bool _isDestory)
{
	//아이템 브릭이였을시에 취할 행동
	if (!m_isEmpty)
	{
		StartAnimation();
		//종현 오빠가 만든 아이템 생성 함수 이쪽에 추가

		//
		m_isEmpty = true;
	}
	// Empty일 경우 액션은 취하지 않는다

	if (m_isInvisible)
		m_isInvisible = false;
}
