#include "ItemBlock.h"
#include "ScrollMgr.h"
#include "Manager.h"
#include "AbstractFactory.h"

CItemBlock::CItemBlock()
	: m_isEmpty(false)
	, m_isReverse(false)
{
}


CItemBlock::~CItemBlock()
{

}

void CItemBlock::CreateBlock(float _fX, float _fY, BLOCK::ID _type, bool _isInvisible)
{
	auto obj = CAbstractFactory<CItemBlock>::Create(_fX, _fY);
	static_cast<CItemBlock*>(obj)->Setup(_type, _isInvisible);
	CObjMgr::Get_Instance()->Add_Object(OBJ::OBSTACLE, obj);
}

void CItemBlock::Initialize(void)
{
	CBlock::Initialize();
}

int CItemBlock::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fY == m_fJumpY)
	{
		m_iGravity = 0;
		m_tInfo.fY = m_fJumpY;
	}
	Update_Rect();
	UpdateAnimation();

	return OBJ_NOEVENT;
}

void CItemBlock::Late_Update(void)
{

}

void CItemBlock::Render(HDC hDC)
{
	if (m_isInvisible)
		return;

	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right + ScrollX, m_tRect.bottom);

}

void CItemBlock::Release(void)
{
}

void CItemBlock::Setup(BLOCK::ID _type, bool _isInvisible)
{
	m_eBlockID = _type;
	m_isInvisible = _isInvisible;
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
	CBlock::StartAnimation();
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
	// �μ����� ��ƼŬ�� ������ ���ʿ��ٰ� �߰� ����

	//
}

void CItemBlock::PlayAction(bool _isDestory)
{
	switch (m_eBlockID)
	{
		case BLOCK::ID::DEFAULT:
		{
			//�⺻ �긯�̿����ÿ� ���� �ൿ

			if (_isDestory)
				DestoryBlock();
			else
				StartAnimation();
			break;
		}

		case BLOCK::ID::ITEM:
		{
			//������ �긯�̿����ÿ� ���� �ൿ
			if (!m_isEmpty)
			{
				StartAnimation();
				//���� ������ ���� ������ ���� �Լ� ���ʿ� �߰�

				//
				m_isEmpty = true;
			}

			// Empty�� ��� �׼��� ������ �ʴ´�
			break;
		}
	}

	if (m_isInvisible)
		m_isInvisible = false;
}
