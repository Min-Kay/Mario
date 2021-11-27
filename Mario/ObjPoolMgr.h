#pragma once
#include "Include.h"

class CObj;

class CObjPoolMgr
{

private:
	CObjPoolMgr();
	~CObjPoolMgr();

public:
	void	Release();

public:
	void	Spawn(MONSTER::ID _monster, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);

private:
	vector<CObj*> obj_pool[MONSTER::END];

public:
	static CObjPoolMgr* Get_Instance()
	{
		if (!pInstance)
			pInstance = new CObjPoolMgr;

		return pInstance;
	}

	static void	Destroy_Instance()
	{
		if (pInstance)
		{
			delete pInstance;
			pInstance = nullptr; 
		}
	}

private:
	static	CObjPoolMgr* pInstance;

};

