#include "ObjPoolMgr.h"
#include "Obj.h"
#include "Manager.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Monster1.h"

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
		for_each(obj_pool[i].begin(), obj_pool[i].end(), CDeleteObj());
	}
}

void CObjPoolMgr::Spawn(MONSTER::ID _monster, float _X , float _Y, DIR::DIR _dir)
{
	for (auto& i : obj_pool[_monster])
	{
		if (i->Get_Dead())
		{
			i->Initialize(); 
			i->Set_Pos(_X, _Y);
			i->Set_Direction(_dir);
			i->Update_Rect();
			i->Set_Dead(false);
			CObjMgr::Get_Instance()->Add_Object(OBJ::MONSTER,i);
			return;
		}
	}

	switch (_monster)
	{
	case MONSTER::MONSTER:
		obj_pool[_monster].push_back(CAbstractFactory<CMonster>::Create(_X,_Y, _dir));
		break;
	case MONSTER::JUMPER:
		obj_pool[_monster].push_back(CAbstractFactory<CMonster1>::Create(_X, _Y, _dir));
		break;
	default:
		return;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ::MONSTER, obj_pool[_monster].back());

}
