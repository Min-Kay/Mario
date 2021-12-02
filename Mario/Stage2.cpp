#include "Stage2.h"
#include "Manager.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Coin.h"
#include "ItemBlock.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	isClear = false;
	isFail = false;
	Set_GameNum(GAME::STAGETWO);
	m_result = GAME::NONE;
	CLineMgr::Get_Instance()->Load(LOAD_STAGETWO);
	CObjPoolMgr::Get_Instance()->Load_Obstacles(LOAD_STAGETWO_BLOCK);
	CBmpMgr::Get_Instance()->Insert_Bmp(BACKGROUND_SNOW_BMP,BACKGROUND_SNOW_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CASTLE_BMP,CASTLE_KEY);
	CObjMgr::Get_Instance()->Add_Object(OBJ::PLAYER, CAbstractFactory<CPlayer>::Create());
	m_Time = GetTickCount(); 
	Init_Ui();

	savePoint.push_back({ 100,100 });
	savePoint.push_back({ 2100,100 });
	savePoint.push_back({ 3000,100 });
	savePoint.push_back({ 4000,100 });
	savePoint.push_back({ 5000,100 });

	endLine = { (long)7000.f,(long)320.f};

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 754, 200, DIR::RIGHT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1466, 200, DIR::RIGHT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1898, 200, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 1952, 200, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 2476, 200);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 2865, 200);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, 2902, 200);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3400, 431, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, 3450, 431, DIR::LEFT);

	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 3791, 431, DIR::LEFT);
	
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::SQUID, 4429, 431, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::SQUID, 4474, 300, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::SQUID, 4544, 300, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::SQUID, 4586, 300, DIR::LEFT);
	
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 6204, 431, DIR::LEFT);
	CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, 6250, 431, DIR::LEFT);

	CObjPoolMgr::Get_Instance()->Spawn_Obstacle(BLOCK::PIPE, 1500, 431);

}

void CStage2::Update()
{
	Key_Input();
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();



}

void CStage2::Late_Update()
{
	Fall_Down();
	CLineMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CDataMgr::Get_Instance()->Late_Update();
	Update_SavePoint(); 
	Check_EndLine(); 
	Check_State();
}

void CStage2::Render(HDC _hdc)
{
	if (m_result == GAME::NONE)
	{
		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(BACKGROUND_SNOW_KEY);
		BitBlt(_hdc, 0, 0, WINCX, WINCY, DrawingDC, 0, 0, SRCCOPY);

		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(CASTLE_KEY);
		GdiTransparentBlt(_hdc, int(endLine.x + 130 + CScrollMgr::Get_Instance()->Get_ScrollX()), endLine.y, 130, 130, DrawingDC, 0, 0, 130, 130, RGB(255, 255, 255));

		CLineMgr::Get_Instance()->Render(_hdc);
		CObjMgr::Get_Instance()->Render(_hdc);

		Render_Data(_hdc);
	}
	else
		Result(_hdc);
}

void CStage2::Release()
{
	CScrollMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CBmpMgr::Get_Instance()->Release();

	savePoint.erase(savePoint.begin(),savePoint.end()); 
	savePoint.clear();
}
