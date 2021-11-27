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

CObj* CObjMgr::Get_Target(OBJ::ID _eID, CObj* pObj)
{
	CObj*		pTarget = nullptr;

	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[_eID])
	{
		float fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;
		float fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDistance > fDiagonal || !pTarget)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
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
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}
