#pragma once
#include "Bullet.h"
class CFlowerBullet :
    public CBullet
{
public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);


	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

};

