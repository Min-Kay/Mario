#include "ObjPoolMgr.h"
#include "Obj.h"
#include "Manager.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Monster1.h"
#include "Bullet.h"
#include "Coin.h"

CObjPoolMgr* CObjPoolMgr::pInstance = nullptr;

CObjPoolMgr::CObjPoolMgr()
{
}

CObjPoolMgr::~CObjPoolMgr()
{
}

void CObjPoolMgr::Release()
{
	for (int i = 0; i < MONSTER::END; ++i)
	{
		for_each(monster_pool[i].begin(), monster_pool[i].end(), CDeleteObj());
		monster_pool[i].clear();
	}

	for (int i = 0; i < BULLET::END; ++i)
	{
		for_each(bullet_pool[i].begin(), bullet_pool[i].end(), CDeleteObj());
		bullet_pool[i].clear();
	}

	for (int i = 0; i < ITEM::END; ++i)
	{
		for_each(item_pool[i].begin(), item_pool[i].end(), CDeleteObj());
		item_pool[i].clear();
	}
}

void CObjPoolMgr::Spawn_Monster(MONSTER::ID _monster, float _X , float _Y, DIR::DIR _dir)
{
	for (auto& i : monster_pool[_monster])
	{
		if (i->Get_Dead())
		{
			i->Initialize(); 
			i->Set_Pos(_X, _Y);
			i->Set_Direction(_dir);
			i->Set_Dead(false);
			i->Update_Rect();
			CObjMgr::Get_Instance()->Add_Object(OBJ::MONSTER,i);
			return;
		}
	}

	switch (_monster)
	{
	case MONSTER::MONSTER:
		monster_pool[_monster].push_back(CAbstractFactory<CMonster>::Create(_X,_Y, _dir));
		break;
	case MONSTER::JUMPER:
		monster_pool[_monster].push_back(CAbstractFactory<CMonster1>::Create(_X, _Y, _dir));
		break;
	default:
		return;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ::MONSTER, monster_pool[_monster].back());

}

void CObjPoolMgr::Spawn_Bullet(BULLET::ID _bullet, float _X, float _Y, DIR::DIR _dir)
{
	for (auto& i : bullet_pool[_bullet])
	{
		if (i->Get_Dead())
		{
			i->Initialize();
			i->Set_Pos(_X, _Y);
			i->Set_Direction(_dir);
			i->Update_Rect();
			i->Set_Dead(false);
			CObjMgr::Get_Instance()->Add_Object(OBJ::BULLET, i);
			return;
		}
	}

	switch (_bullet)
	{
	case BULLET::BULLET:
		bullet_pool[_bullet].push_back(CAbstractFactory<CBullet>::Create(_X, _Y, _dir));
		break;
	default:
		return;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ::BULLET, bullet_pool[_bullet].back());
}

void CObjPoolMgr::Spawn_Item(ITEM::ID _item, float _X, float _Y, DIR::DIR _dir)
{
	for (auto& i : item_pool[_item])
	{
		if (i->Get_Dead())
		{
			i->Initialize();
			i->Set_Pos(_X, _Y);
			i->Set_Direction(_dir);
			i->Update_Rect();
			i->Set_Dead(false);
			CObjMgr::Get_Instance()->Add_Object(OBJ::ITEM, i);
			return;
		}
	}

	switch (_item)
	{
	case ITEM::COIN:
		item_pool[_item].push_back(CAbstractFactory<CCoin>::Create(_X, _Y));
		break;
	default:
		return;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ::ITEM, item_pool[_item].back());
}
