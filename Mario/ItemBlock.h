#pragma once

#include "Block.h"

class CItemBlock : public CBlock
{
public:
	CItemBlock();
	~CItemBlock();

	static void CreateBlock(float _fX, float _fY, BLOCK::ID _type, bool _isInvisible = false);
public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
	virtual void	Setup(BLOCK::ID _type, bool _isInvisible = false) override;

	virtual void	Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

	virtual void	StartAnimation() override;
	virtual void	UpdateAnimation() override;
	virtual void	DestoryBlock() override;

	void PlayAction(bool _isDestory);


public:
	bool m_isEmpty; //박스가 비어있는 상태인지
	bool m_isReverse;


};

