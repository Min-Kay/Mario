#include "Stage3.h"
#include "Manager.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Coin.h"
#include "ItemBlock.h"

CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	isClear = false;
	isFail = false;
	Set_GameNum(GAME::STAGETHREE);
	m_result = GAME::NONE;
	CLineMgr::Get_Instance()->Load(LOAD_STAGETHREE);
	CObjPoolMgr::Get_Instance()->Load_Obstacles(LOAD_STAGETHREE_BLOCK);
	CBmpMgr::Get_Instance()->Insert_Bmp(BACKGROUND_BMP,BACKGROUND_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(ENDFLAG_BMP,ENDFLAG_KEY);
	CObjMgr::Get_Instance()->Add_Object(OBJ::PLAYER, CAbstractFactory<CPlayer>::Create());
	Init_Ui();

	savePoint.push_back({ 0,100 });
	savePoint.push_back({ 2000,100 });
	savePoint.push_back({ 3000,100 });
	savePoint.push_back({ 4000,100 });
	savePoint.push_back({ 5000,100 });
	savePoint.push_back({ 7000,100 });
	savePoint.push_back({ 8000,100 });

	endLine = { (long)8100 , (long)310};

	CBmpMgr::Get_Instance()->Insert_Bmp(FLOOR_BMP, FLOOR_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CASTLE_BMP, CASTLE_KEY);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 300, 380);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 300 , 400); 
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 400, 400);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 1200, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1250, 400);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 1500, 400);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 300, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 2500, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 2500, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3000, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 3000, 400);


	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 3500, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3700, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 4000, 400);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 4300, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 4500, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 4700, 400);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 5000, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 5500, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 5700, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 5500, 400);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 6000, 380);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 6200, 400);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 6500, 400);

}

void CStage3::Update()
{
	Key_Input();
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

}

void CStage3::Late_Update()
{
	Fall_Down();
	CLineMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CDataMgr::Get_Instance()->Late_Update();
	Update_SavePoint(); 
	Check_EndLine(); 
	Check_State();
}

void CStage3::Render(HDC _hdc)
{
	if (m_result == GAME::NONE)
	{
		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(BACKGROUND_KEY);
		BitBlt(_hdc, 0, 0, WINCX, WINCY, DrawingDC, 0, 0, SRCCOPY);

		float x = CScrollMgr::Get_Instance()->Get_ScrollX();
		
		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(CASTLE_KEY);
		GdiTransparentBlt(_hdc, int(endLine.x + 130 + x), endLine.y, 130, 130, DrawingDC, 0, 0, 130, 130, RGB(255, 255, 255));

		//CLineMgr::Get_Instance()->Render(_hdc);
		CObjMgr::Get_Instance()->Render(_hdc);

		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(FLOOR_KEY);

		GdiTransparentBlt(_hdc, int(0 + x), 548, 8518, 52, DrawingDC, 0, 0, 8518, 52, RGB(255, 255, 255));
		GdiTransparentBlt(_hdc, int(0 + x), 496, 8518, 52, DrawingDC, 0, 0, 8518, 52, RGB(255, 255, 255));
		GdiTransparentBlt(_hdc, int(0 + x), 446, 8518, 52, DrawingDC, 0, 0, 8518, 52, RGB(255, 255, 255));


		Render_Data(_hdc);
	}
	else
		Result(_hdc);
}

void CStage3::Release()
{
	CScrollMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CBmpMgr::Get_Instance()->Release();

	savePoint.erase(savePoint.begin(),savePoint.end()); 
	savePoint.clear();
}
