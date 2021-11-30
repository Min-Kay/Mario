#pragma once
#include "Item.h"

class CMushroom : public CItem
{
public:
	CMushroom();
	~CMushroom();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);
	virtual void		Set_Pos(float _fX, float _fY) override;

	virtual void		Set_Collision(OBJ::ID _id, DIR::DIR _dir, float _fWidth = 0.f, float _fHeight = 0.f);

public:
	void				Gravity(void);
	void				Moving(void);
	void				StartAnimation(void);
	void				OnTheBlock(float _fY);

private:
	bool			m_IsObjCol;
	bool			m_isAni;
	float			m_OriginY;
	float			m_fY; // 충돌하는 y값
};