#include "Stage1.h"
#include "Manager.h"
#include "Player.h"
#include "AbstractFactory.h"


CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize()
{
	isClear = false;
	isFail = false;
	Set_GameNum(GAME::STAGEONE);
	m_result = GAME::NONE;
	CLineMgr::Get_Instance()->Load(LOAD_STAGEONE);
	CBmpMgr::Get_Instance()->Insert_Bmp(BACKGROUND_BMP,BACKGROUND_KEY);
	CObjMgr::Get_Instance()->Add_Object(OBJ::PLAYER, CAbstractFactory<CPlayer>::Create());
	m_Time = GetTickCount(); 
}

void CStage1::Update()
{
	Key_Input();
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (m_Time + 1500.f < GetTickCount())
	{
		CObjPoolMgr::Get_Instance()->Spawn(MONSTER::JUMPER,200,200);
		m_Time = GetTickCount(); 
	}
}

void CStage1::Late_Update()
{
	CLineMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	Check_State();
}

void CStage1::Render(HDC _hdc)
{
	if (m_result == GAME::NONE)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(BACKGROUND_KEY);
		BitBlt(_hdc,0,0,WINCX,WINCY,hMemDC,0,0,SRCCOPY);

		CLineMgr::Get_Instance()->Render(_hdc);
		CObjMgr::Get_Instance()->Render(_hdc);
	}
	else
		Result(_hdc);
}

void CStage1::Release()
{
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
}
