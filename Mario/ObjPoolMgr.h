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
	void	Spawn_Monster(MONSTER::ID _monster, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);
	void	Spawn_Bullet(BULLET::ID _bullet, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);
	void	Spawn_Item(ITEM::ID _item, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);
	void	Spawn_Obstacle(BLOCK::ID _item, float _X, float _Y);

public:
	void	Load_Obstacles(const TCHAR* _file);

private:
	vector<CObj*> monster_pool[MONSTER::END];
	vector<CObj*> bullet_pool[BULLET::END];
	vector<CObj*> item_pool[ITEM::END];
	vector<CObj*> obstacle_pool[BLOCK::END];


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

