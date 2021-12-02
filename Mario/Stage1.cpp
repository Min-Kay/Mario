#include "Stage1.h"
#include "Manager.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Coin.h"
#include "ItemBlock.h"
#include "Pipe.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	isClear = false;
	isFail = false;
	Set_GameNum(GAME::STAGEONE);
	m_result = GAME::NONE;
	CLineMgr::Get_Instance()->Load(LOAD_STAGEONE);
	CObjPoolMgr::Get_Instance()->Load_Obstacles(LOAD_STAGEONE_BLOCK);

	// ±¼¶Ò
	CObjPoolMgr::Get_Instance()->Spawn_Obstacle(BLOCK::PIPE, 1045.f, 410.f);
	CObjPoolMgr::Get_Instance()->Spawn_Obstacle(BLOCK::PIPE, 1400.f, 410.f);
	CObjPoolMgr::Get_Instance()->Spawn_Obstacle(BLOCK::PIPE, 5850.f, 450.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(BACKGROUND_BMP,BACKGROUND_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CASTLE_BMP,CASTLE_KEY);
	CObjMgr::Get_Instance()->Add_Object(OBJ::PLAYER, CAbstractFactory<CPlayer>::Create());

	CDataMgr::Get_Instance()->Initialize();


	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 980, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::SQUID, 980, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 900, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 980, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 980, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1456, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1890, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1950, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3030, 148);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3550, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3650, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, 4000, 418);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 4400, 418);

	//m_Time = GetTickCount(); 
	Init_Ui();

	savePoint.push_back({ 100,100 });
	savePoint.push_back({ 2000,100 });
	savePoint.push_back({ 3000,100 });
	savePoint.push_back({ 4000,100 });
	savePoint.push_back({ 5000,100 });
	savePoint.push_back({ 7000,100 });
	savePoint.push_back({ 8000,100 });

	endLine = { (long)6800.f, (long)320 };

	CBmpMgr::Get_Instance()->Insert_Bmp(GROUND_BMP, GROUND_KEY);
}

void CStage1::Update()
{
	Key_Input();
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CStage1::Late_Update()
{
	Fall_Down();
	CLineMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CDataMgr::Get_Instance()->Late_Update();
	Update_SavePoint(); 
	Check_EndLine(); 
	Check_State();
}

void CStage1::Render(HDC _hdc)
{
	if (m_result == GAME::NONE)
	{
		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(BACKGROUND_KEY);
		BitBlt(_hdc, 0, 0, WINCX, WINCY, DrawingDC, 0, 0, SRCCOPY);

		float x = CScrollMgr::Get_Instance()->Get_ScrollX();
	
		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(GROUND_KEY);
		GdiTransparentBlt(_hdc, int(x), 450, 7554, 270, DrawingDC, 0, 0, 7554, 270, RGB(255, 255, 255));

		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(CASTLE_KEY);
		GdiTransparentBlt(_hdc, int(endLine.x + 130 + x), endLine.y, 130, 130, DrawingDC, 0, 0, 130, 130, RGB(255, 255, 255));

		CObjMgr::Get_Instance()->Render(_hdc);

		Render_Data(_hdc);
	}
	else
		Result(_hdc);
}

void CStage1::Release()
{
	CScrollMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CBmpMgr::Get_Instance()->Release();

	savePoint.erase(savePoint.begin(),savePoint.end()); 
	savePoint.clear();
}
