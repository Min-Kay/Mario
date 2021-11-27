#include "framework.h"
#include "ObjMgr.h"
#include "Obj.h"

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
	for (int i = 0; i < OBJ::END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); )
		{
			int	iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				if ((*iter)->Get_ID() != OBJ::MONSTER)
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
		if (i == OBJ::MONSTER)
		{
			m_ObjList[i].clear();
			continue;
		}
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

const float& CObjMgr::Get_Player_X() const
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return 0;

	return m_ObjList[OBJ::PLAYER].front()->Get_Info().fX;
}

void CObjMgr::Set_Player_Pos(float _x, float _y)
{
	if (m_ObjList[OBJ::PLAYER].empty())
		return;
	
	m_ObjList[OBJ::PLAYER].front()->Set_Pos(_x,_y);
	m_ObjList[OBJ::PLAYER].front()->Update_Rect();
}
