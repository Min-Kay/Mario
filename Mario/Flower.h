#pragma once
#include "Item.h"
class CFlower :
	public CItem
{
public:
	CFlower();
	~CFlower();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);
	virtual void		Set_Pos(float _fX, float _fY) override;

	virtual void		Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth = 0.f, float _fHeight = 0.f);

public:
	void				StartAnimation(void);
	void				Gravity(void);

private:
	bool			m_IsObjCol;
	bool			m_isAni;
	float			m_OriginY;
	float			m_fY; // 충돌하는 y값
	
	DWORD			m_AnimTimer;
	int				m_Count;
};