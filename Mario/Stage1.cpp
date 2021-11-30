#include "Stage1.h"
#include "Manager.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Coin.h"
#include "ItemBlock.h"

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
	CBmpMgr::Get_Instance()->Insert_Bmp(BACKGROUND_BMP,BACKGROUND_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(ENDFLAG_BMP,ENDFLAG_KEY);
	CObjMgr::Get_Instance()->Add_Object(OBJ::PLAYER, CAbstractFactory<CPlayer>::Create());
	CDataMgr::Get_Instance()->Initialize();
	m_Time = GetTickCount(); 
	Init_Ui();

	savePoint.push_back({ 100,100 });
	savePoint.push_back({ 2000,100 });
	savePoint.push_back({ 3000,100 });
	savePoint.push_back({ 4000,100 });
	savePoint.push_back({ 5000,100 });
	savePoint.push_back({ 7000,100 });
	savePoint.push_back({ 8000,100 });

	endLine = { (long)8100 , (long)310};

	CBmpMgr::Get_Instance()->Insert_Bmp(FLOOR_BMP, FLOOR_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(CASTLE_BMP, CASTLE_KEY);

}

void CStage1::Update()
{
	Key_Input();
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (m_Time + 5000.f < GetTickCount())
	{
		//CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::GOOMBA, rand() % 400 + 300, 300);
		//CObjPoolMgr::Get_Instance()->Spawn_Item(ITEM::COIN, rand() % 400 + 300, 300);
		//CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::KOOPA, rand() % 400 + 300, 300);
		CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::SQUID, rand() % 400 + 300, 300);
		//CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::FLOWER, rand() % 400 + 300, 300);
		//CObjPoolMgr::Get_Instance()->Spawn_Monster(MONSTER::CHICKEN, rand() % 400 + 300, 300);
		m_Time = GetTickCount(); 
	}
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

		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(FLOOR_KEY);
		float x = CScrollMgr::Get_Instance()->Get_ScrollX();

		GdiTransparentBlt(_hdc, int(0 + x), 548, 8518, 52, DrawingDC, 0, 0, 8518, 52, RGB(255, 255, 255));
		GdiTransparentBlt(_hdc, int(0 + x), 496, 8518, 52, DrawingDC, 0, 0, 8518, 52, RGB(255, 255, 255));
		GdiTransparentBlt(_hdc, int(0 + x), 446, 8518, 52, DrawingDC, 0, 0, 8518, 52, RGB(255, 255, 255));
		
		//�� �׸���
		DrawingDC = CBmpMgr::Get_Instance()->Find_Image(CASTLE_KEY);
		GdiTransparentBlt(_hdc, int(endLine.x + 130 + x), endLine.y, 130, 130, DrawingDC, 0, 0, 130, 130, RGB(255, 255, 255));

		CLineMgr::Get_Instance()->Render(_hdc);
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
