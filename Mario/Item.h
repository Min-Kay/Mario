#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);

	virtual void		Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth = 0.f, float _fHeight = 0.f);
	 const ITEM::ID& Get_ItemId()  const { return m_itemId; }
	 const bool& Get_Vaild() const { return m_Vaild; }
protected:
	float			m_Force = 0.f; // 아래로 가하는 힘
	float			m_fGravity = 0.5f; // 중력은 모두가 가지고 있어야하는거 static 만들면 좋을것
	ITEM::ID		m_itemId;
	bool			m_Vaild;
	DWORD			m_VaildTime;
};

