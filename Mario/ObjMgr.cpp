#include "framework.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}


void CObjMgr::Add_Object(OBJ::ID eID, CObj* pObj)
{
	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::PLAYER],m_ObjList[OBJ::MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::MONSTER], m_ObjList[OBJ::BULLET]);

	for (int i = 0; i < OBJ::END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); )
		{
			int	iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				if (i != OBJ::BULLET && i != OBJ::MONSTER)
					Safe_Delete(*iter);

				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CObjMgr::Render(HDC m_DC)
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		if (i == OBJ::MONSTER || i == OBJ::BULLET)
		{
			m_ObjList[i].clear();
			continue;
		}
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

const RECT& CObjMgr::Get_Player_RECT() const
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return {};

	return m_ObjList[OBJ::PLAYER].front()->Get_Rect();
}

void CObjMgr::Set_Player_Jump(bool _bool)
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return;

	static_cast<CPlayer*>(m_ObjList[OBJ::PLAYER].front())->Set_Jump(false);
}

void CObjMgr::Set_Player_Pos(float _x, float _y)
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return;
	
	m_ObjList[OBJ::PLAYER].front()->Set_State(STATE::IDLE);
	m_ObjList[OBJ::PLAYER].front()->Set_Pos(_x,_y);
	m_ObjList[OBJ::PLAYER].front()->Update_Rect();
}

void CObjMgr::Set_Player_Die(bool _bool)
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return;

	m_ObjList[OBJ::PLAYER].front()->Set_Dead(_bool);
}

const bool& CObjMgr::Get_Player_Die() const
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return false;

	if (m_ObjList[OBJ::PLAYER].front()->Get_Dead())
		return true; 

	return false;
}
