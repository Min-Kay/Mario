#include "Item.h"

void CItem::Initialize(void)
{
	m_eID = OBJ::ITEM;
}

int CItem::Update(void)
{
	return 0;
}

void CItem::Late_Update(void)
{
}

void CItem::Render(HDC hDC)
{
}

void CItem::Release(void)
{
}

void CItem::Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth, float _fHeight)
{
}
