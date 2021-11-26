#pragma once
#include "Obj.h"
//#include "Menu.h"
#include <functional>
class CGameButton : public CObj
{
public:
	CGameButton();
	~CGameButton();
	
public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);
	void				SetupButton(float fWidth, float fHeight, float fX, float fY, MENU::KIND _eKind);
	void SeButtonCallBack(float fWidth, float fHeight, float fX, float fY, MENU::KIND _eKind, std::function<void()> _func);
	void OnClick();

private:
	std::function<void()> m_callBack;
	MENU::KIND  m_eType;
};

