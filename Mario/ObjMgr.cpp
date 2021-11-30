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
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::PLAYER], m_ObjList[OBJ::ITEM]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::PLAYER], m_ObjList[OBJ::MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::PLAYER], m_ObjList[OBJ::OBSTACLE]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::PLAYER], m_ObjList[OBJ::BULLET]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::MONSTER], m_ObjList[OBJ::BULLET]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ::PLAYER], m_ObjList[OBJ::ITEM]);

	
	if (!m_ObjList[OBJ::PLAYER].empty())
	{
		if (!m_ObjList[OBJ::PLAYER].front()->Get_Dead() && CCollisionMgr::Collision_Rect_List(static_cast<CPlayer*>(m_ObjList[OBJ::PLAYER].front())->Get_CollisionY(), static_cast<CPlayer*>(m_ObjList[OBJ::PLAYER].front())->Get_CollisionRect(), m_ObjList[OBJ::OBSTACLE]))
		{
			CCollisionMgr::Collision_RectPush(m_ObjList[OBJ::OBSTACLE], m_ObjList[OBJ::PLAYER]);
			static_cast<CPlayer*>(m_ObjList[OBJ::PLAYER].front())->Set_OnBlock(true);
		}
		else
		{
			static_cast<CPlayer*>(m_ObjList[OBJ::PLAYER].front())->Set_OnBlock(false);
		}
	}

	for (int i = 0; i < OBJ::END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); )
		{
			int	iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				if (i != OBJ::BULLET && i != OBJ::MONSTER && i != OBJ::ITEM && i != OBJ::OBSTACLE)
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
		if (i == OBJ::MONSTER || i == OBJ::BULLET || i == OBJ::ITEM)
		{
			m_ObjList[i].clear();
			continue;
		}
		else if (i == OBJ::OBSTACLE)
		{
			for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CKillObj());
			m_ObjList[i].clear();
			continue;
		}
		else
		{
			for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
			m_ObjList[i].clear();
		}
	}
}

list<CObj*> CObjMgr::Get_ObjList(OBJ::ID _id)
{
	return m_ObjList[_id];
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
