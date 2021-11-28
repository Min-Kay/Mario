#pragma once
#include "framework.h"

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);
	static void	Collision_RectPush(list<CObj*> _Dest, list<CObj*> _Src);
	static bool Collision_Mouse(CObj* _Dest);

private:
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);
	static bool Check_Mouse(CObj* _pObj);

};

