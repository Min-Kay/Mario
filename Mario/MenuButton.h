#pragma once
#include "Obj.h"

class CMenuButton : public CObj
{
public:
	CMenuButton();
	~CMenuButton();

public:
	virtual void		Initialize(void) {};
	virtual int			Update(void) { return OBJ_NOEVENT; };
	virtual void		Late_Update(void) {};
	virtual void		Render(HDC hDC) {};
	virtual void		Release(void) {};
	virtual GAME::ID	Menu_Result() { return GAME::ID_END; };
};

