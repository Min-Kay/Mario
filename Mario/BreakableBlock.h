#pragma once
#include "Block.h"
class CBreakableBlock :
	public CBlock
{

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override {};
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override {};

	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

public:
	virtual void	Set_Pos(float _x, float _y) override;
	virtual void	StartAnimation();
	virtual void	UpdateAnimation();
	virtual void	DestoryBlock();

	void PlayAction(bool _isDestory);

private: 
	bool			m_isReverse;
	bool			m_isAni;
	float			m_originPosX;
	float			m_originPosY;
	float			m_AniTickDelay;
	bool			m_isSpriteAni;

	DWORD			m_OldTickCount;

};

