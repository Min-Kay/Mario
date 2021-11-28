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
	
	//���ϸ��̼� ���� �Լ� // ��� ������ �ش� �޼��� ȣ���ϸ� ��
	virtual void StartAnimation();
	//�ִϸ��̼� ���ư��� �ϴ� ������Ʈ �Լ� Update�� ������ ������ ��.
	virtual void UpdateAnimation();
	//��� �ı� �Լ�
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

