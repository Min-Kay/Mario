#pragma once

#include "Obj.h"

class CBlock : public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override {};
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override {};

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override {};

public:
	virtual void	Setup(BLOCK::ID _type , bool _isInvisible = false);
	virtual void	StartAnimation() {};
	virtual void	UpdateAnimation() {};
	virtual void	DestoryBlock() {};

public:
	const BLOCK::ID& Get_BlockId() const { return m_eBlockID; };

protected:
	BLOCK::ID		m_eBlockID;
	bool			m_isInvisible;
	HDC				hMemDC;
};

