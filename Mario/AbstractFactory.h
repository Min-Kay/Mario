#pragma once

#include "Obj.h"
#include "Enum.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, DIR::DIR eDir = DIR::RIGHT)
	{
		CObj*		pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();
		pObj->Set_Direction(eDir);
		pObj->Update_Rect();

		return pObj;
	}


};

