#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "CollisionMgr.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void		Add_Object(OBJ::ID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC m_DC);
	void		Release(void);

public:
	const RECT& Get_Player_RECT() const ;
	void		Set_Player_Jump(bool _bool);
	void		Set_Player_Pos(float _x, float _y);
	void		Set_Player_Die(bool _bool);
	const bool& Get_Player_Die() const;

private:
	list<CObj*>		m_ObjList[OBJ::END];

public:
	static	CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
				m_pInstance = new CObjMgr;
		
		return m_pInstance;
	}

	static	void		Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*			m_pInstance;

};

