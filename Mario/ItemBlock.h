#pragma once

#include "Block.h"
#include "ObjMgr.h"
#include "Obj.h"

class CItemBlock : public CBlock
{
public:
	CItemBlock();
	~CItemBlock();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
	virtual void	Set_Pos(float _fX, float _fY) override;
	void	Setup(BLOCK::ID _type, bool _isInvisible = false);

	virtual void	Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;

	void	StartAnimation();
	void	UpdateAnimation();
	void	DestoryBlock();

	//스프라이트 에니메이션
	void	UpdateSpriteAnimation();

	void PlayAction(bool _isDestory);

private:

	bool			m_isEmpty;
	bool			m_isReverse;
	bool			m_isAni;
	float			m_originPosX;
	float			m_originPosY;

//SpriteAni
	TCHAR*			m_SpriteImageKeys[5];
	int				m_curSpriteImageIdx;
	float			m_AniTickDelay;
	bool			m_isSpriteAni;

	DWORD			m_OldTickCount;
};

