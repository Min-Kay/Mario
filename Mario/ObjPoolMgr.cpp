#include "ObjPoolMgr.h"
#include "Obj.h"
#include "Manager.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Bullet.h"
#include "Coin.h"
#include "Koopa.h"
#include "ItemBlock.h"
#include "BreakableBlock.h"
#include "Mushroom.h"
#include "Flower.h"
#include "Chicken.h"
#include "Squid.h"
#include "MonsterFlower.h"
#include "Koopa_bullet.h"

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

	for (int i = 0; i < BLOCK::END; ++i)
	{
		for_each(obstacle_pool[i].begin(), obstacle_pool[i].end(), CDeleteObj());
		obstacle_pool[i].clear();
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
	case MONSTER::GOOMBA:
		monster_pool[_monster].push_back(CAbstractFactory<CMonster>::Create(_X,_Y, _dir));
		break;
	case MONSTER::CHICKEN:
		monster_pool[_monster].push_back(CAbstractFactory<CChicken>::Create(_X, _Y, _dir));
		break;
	case MONSTER::KOOPA:
		monster_pool[_monster].push_back(CAbstractFactory<CKoopa>::Create(_X, _Y, _dir));
		break;
	case MONSTER::SQUID:
		monster_pool[_monster].push_back(CAbstractFactory<CSquid>::Create(_X, _Y, _dir));
		break;
	case MONSTER::FLOWER:
		monster_pool[_monster].push_back(CAbstractFactory<CMonsterFlower>::Create(_X, _Y, _dir));
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
			i->Set_Pos(_X, _Y);
			i->Initialize();
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
	case BULLET::KOOPA_BULLET:
		bullet_pool[_bullet].push_back(CAbstractFactory<CKoopa_bullet>::Create(_X, _Y, _dir));
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
	case ITEM::MUSHROOM:
		item_pool[_item].push_back(CAbstractFactory<CMushroom>::Create(_X, _Y));
		break;
	case ITEM::FLOWER:
		item_pool[_item].push_back(CAbstractFactory<CFlower>::Create(_X, _Y));
		break;
	default:
		return;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ::ITEM, item_pool[_item].back());
}

void CObjPoolMgr::Spawn_Obstacle(BLOCK::ID _item, float _X, float _Y)
{
	for (auto& i : obstacle_pool[_item])
	{
		if (i->Get_Dead())
		{
			i->Initialize();
			i->Set_Pos(_X, _Y);
			i->Update_Rect();
			i->Set_Dead(false);
			CObjMgr::Get_Instance()->Add_Object(OBJ::OBSTACLE, i);
			return;
		}
	}

	switch (_item)
	{
	case BLOCK::DEFAULT:
		obstacle_pool[_item].push_back(CAbstractFactory<CBlock>::Create(_X, _Y));
		break;
	case BLOCK::ITEM:
		obstacle_pool[_item].push_back(CAbstractFactory<CItemBlock>::Create(_X, _Y));
		break;
	case BLOCK::INVISIBLE:
	{
		CObj* temp = CAbstractFactory<CItemBlock>::Create(_X, _Y);
		static_cast<CItemBlock*>(temp)->Setup(BLOCK::INVISIBLE,true);
		obstacle_pool[_item].push_back(temp);
	}
		break;
	case BLOCK::BREAKABLE:
		obstacle_pool[_item].push_back(CAbstractFactory<CBreakableBlock>::Create(_X, _Y));
		break;
	default:
		return;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ::OBSTACLE, obstacle_pool[_item].back());
}

void CObjPoolMgr::Load_Obstacles(const TCHAR* _file)
{
	HANDLE			hFile = CreateFile(_file, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD		dwByte = 0;
	BLOCKINFO	binfo{};

	while (true)
	{
		ReadFile(hFile, &binfo, sizeof(BLOCKINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		Spawn_Obstacle(binfo.id,binfo.pos.x, binfo.pos.y);
	}

	CloseHandle(hFile);
}

