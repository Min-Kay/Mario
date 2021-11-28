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
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Set_Pos(float _fX, float _fY) override;

	virtual void Setup(BLOCK::ID _type , bool _isInvisible = false);
	virtual void Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR) override;
	virtual void Gravity();
	
	//에니메이션 시작 함수 // 블록 연출은 해당 메서드 호출하면 됨
	virtual void StartAnimation();
	//애니메이션 돌아가게 하는 업데이트 함수 Update문 내에서 돌리면 됨.
	virtual void UpdateAnimation();
	//블록 파괴 함수
	virtual void	DestoryBlock() {};

public:
	BLOCK::ID	m_eBlockID;
	int		    m_iGravity;
	int			m_iForce;
	bool			m_bJump;
	float			m_fJumpY;
	float			m_fJumpPower;
	float			m_fTime;

	float			m_originPosX;
	float			m_originPosY;

protected:
	bool			m_isAni;
	bool			m_isInvisible;

};

