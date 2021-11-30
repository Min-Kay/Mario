#pragma once
#include "Item.h"

class CCoin :
	public CItem
{
public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);


	virtual void		Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth = 0.f, float _fHeight = 0.f);

private:
	int				m_bmpCount = 0;
	DWORD			m_SpinTime = 0;
};

