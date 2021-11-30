#include "CollisionMgr.h"
#include "MenuButton.h"
#include "Define.h"
#include "Item.h"
#include "Player.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto Dest : _Dest)
	{
		float fWidth = 0.f, fHeight = 0.f;
		for (auto Src : _Src)
		{
			if (Dest->Get_Dead() || Src->Get_Dead())
				continue;

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))
			{
				// 상하
				if (fWidth > fHeight)
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						if (Dest->Get_ID() == OBJ::PLAYER && Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CPlayer*>(Dest)->Set_CollisionItem(static_cast<CItem*>(Src)-> Get_ItemId());
						}
						Dest->Set_Collision(Src->Get_ID(), DIR::DOWN);

						if (Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CItem*>(Src)->Set_Collision(Dest->Get_ID(),DIR::UP,Src->Get_Info().fX, Src->Get_Info().fY);
						}
						else 
							Src->Set_Collision(Dest->Get_ID(), DIR::UP);
					}
					else
					{
						if (Dest->Get_ID() == OBJ::PLAYER && Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CPlayer*>(Dest)->Set_CollisionItem(static_cast<CItem*>(Src)->Get_ItemId());
						}
						Dest->Set_Collision(Src->Get_ID(), DIR::UP);

						if (Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CItem*>(Src)->Set_Collision(Dest->Get_ID(), DIR::DOWN, Src->Get_Info().fX, Src->Get_Info().fY);
						}
						else
							Src->Set_Collision(Dest->Get_ID(), DIR::DOWN);
					}
				}

				// 좌우
				else
				{
					if (Dest->Get_Info().fX < Src->Get_Info().fX)
					{
						if (Dest->Get_ID() == OBJ::PLAYER && Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CPlayer*>(Dest)->Set_CollisionItem(static_cast<CItem*>(Src)->Get_ItemId());
						}
						Dest->Set_Collision(Src->Get_ID(), DIR::RIGHT);

						if (Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CItem*>(Src)->Set_Collision(Dest->Get_ID(), DIR::LEFT, Src->Get_Info().fX, Src->Get_Info().fY);
						}
						else
							Src->Set_Collision(Dest->Get_ID(), DIR::LEFT);
					}
					else
					{
						if (Dest->Get_ID() == OBJ::PLAYER && Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CPlayer*>(Dest)->Set_CollisionItem(static_cast<CItem*>(Src)->Get_ItemId());
						}
						Dest->Set_Collision(Src->Get_ID(), DIR::LEFT);

						if (Src->Get_ID() == OBJ::ITEM)
						{
							static_cast<CItem*>(Src)->Set_Collision(Dest->Get_ID(), DIR::RIGHT, Src->Get_Info().fX, Src->Get_Info().fY);
						}
						else
							Src->Set_Collision(Dest->Get_ID(), DIR::RIGHT);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Collision_Rect_List(float& _y, RECT _Dest, list<CObj*> _Src)
{
	RECT rc{};
	for (auto Src : _Src)
	{
		if (IntersectRect(&rc,&_Dest,&Src->Get_Rect()))
		{
			_y = Src->Get_Rect().top;
			return true;
		}
	}
	return false;
}

void CCollisionMgr::Collision_RectPush(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto Dest : _Dest)
	{
		float fWidth = 0.f, fHeight = 0.f;
		for (auto Src : _Src)
		{
			if (Check_Rect(Dest, Src, &fWidth, &fHeight))
			{
				// 상하
				if (fWidth > fHeight)
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Src->Set_PosY(fHeight);
					}
					else
					{
						Src->Set_PosY(-fHeight);
					}
				}

				// 좌우
				else
				{
					if (Dest->Get_Info().fX < Src->Get_Info().fX)
					{
						Src->Set_PosY(fWidth);
					}
					else
					{
						Src->Set_PosY(-fWidth);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Collision_Mouse(CObj* _Dest)
{
	if (Check_Mouse(_Dest))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			return true;
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight)
{
	float fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if (fWidth < fCX && fHeight < fCY)
	{
		*_pWidth = fCX - fWidth;
		*_pHeight = fCY - fHeight;
		return true;
	}

	else
		return false;
}

bool CCollisionMgr::Check_Mouse(CObj* _pObj)
{
	POINT pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT Button = _pObj->Get_Rect();

	// 마우스 커서가 박스 안에 충돌
	if (pt.x >= Button.left &&
		pt.x <= Button.right &&
		pt.y >= Button.top &&
		pt.y <= Button.bottom)
	{
		return true;
	}

	return false;
}
