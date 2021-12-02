#pragma once
#include "Obj.h"
#include "Enum.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;

	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

	void		Jumping(void);

public:
	void		Set_ParentID(OBJ::ID _id) { parentId = _id; }
	const OBJ::ID& Get_ParentID() const { return parentId; }


protected:
	OBJ::ID		parentId;

private:
	int				m_iCount;	// ¶¥¿¡ ´êÀº È½¼ö ÀúÀåÇÒ º¯¼ö
	bool			m_bJump;
	float			m_fJumpY;
	float			m_fJumpPower;
	float			m_fTime;

	DWORD			m_AnimTime;
		

private:
	int m_AnimNum = 0;
};

