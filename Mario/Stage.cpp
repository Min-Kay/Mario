#include "Stage.h"
#include "Manager.h"

void CStage::Result(HDC _hdc)
{
	switch (m_result) {
	case GAME::WIN:
		Show_Win_Lose(_hdc);
		if (m_GameNum + 1 != GAME::ID_END)
			Set_GameNum(GAME::ID((int)m_GameNum + 1));
		else
			Set_GameNum(GAME::MENU);
		break;
	case GAME::LOSE:
		Show_Win_Lose(_hdc);
		Set_GameNum(GAME::MENU);
		break;
	}
}

void CStage::Show_Win_Lose(HDC _hdc)
{
	DWORD		showTime = GetTickCount();
	TCHAR		szShow[10] = L"";
	RECT		m_BackgroundRect{ 0,0,WINCX,WINCY }, m_TextRect{ WINCX / 2 - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2) };
	HBRUSH		brush = NULL; // 색 설정
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림체")); // 폰트 제작
	oldFont = (HFONT)SelectObject(_hdc, hFont); // 폰트 변경

	switch (m_result)
	{
	case GAME::WIN:
		SetTextColor(_hdc, RGB(0, 255, 0)); // 텍스트 색 설정
		brush = CreateSolidBrush(RGB(0, 150, 0)); // 배경 색 설정
		swprintf_s(szShow, L"승리");
		break;
	case GAME::LOSE:
		SetTextColor(_hdc, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(150, 0, 0));
		swprintf_s(szShow, L"패배");
		break;
	default:
		break;
	}

	Rectangle(_hdc, m_BackgroundRect.left, m_BackgroundRect.top, m_BackgroundRect.right, m_BackgroundRect.bottom);
	HDC m_hdc = GetDC(g_hWnd);
	FillRect(_hdc, &m_BackgroundRect, brush); // RECT에 색 채우기 
	FillRect(_hdc, &m_TextRect, brush);
	TextOut(_hdc, m_TextRect.left, m_TextRect.top, szShow, lstrlen(szShow));

	BitBlt(m_hdc, 0, 0, WINCX, WINCY, _hdc, 0, 0, SRCCOPY);

	while (showTime + 3000 > GetTickCount()){}
}

void CStage::Check_State()
{
	if (isClear)
	{
		Set_Result(GAME::WIN);
	}

	else if(isFail || CDataMgr::Get_Instance()->Get_Life() <= 0)
	{
		CDataMgr::Get_Instance()->Release();
		Set_Result(GAME::LOSE);
	}
}

void CStage::Key_Input()
{
#ifdef _DEBUG
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		isClear = true;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		isFail = true;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
		CDataMgr::Get_Instance()->Add_Coin(10);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F4))
		CDataMgr::Get_Instance()->Add_Life(10);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F6))
		CDataMgr::Get_Instance()->Add_Life(-10);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F7))
		CDataMgr::Get_Instance()->Add_Score(10);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F8))
		Set_Player_To_SavePoint();
#endif // DEBUG
}

void CStage::Render_Data(HDC _hdc)
{
	oldFont = (HFONT)SelectObject(_hdc, hFont); // 폰트 변경
	swprintf_s(score, _T("%d"), CDataMgr::Get_Instance()->Get_Score());
	swprintf_s(coin, _T("%d"), CDataMgr::Get_Instance()->Get_Coin());
	swprintf_s(life, _T("%d"), CDataMgr::Get_Instance()->Get_Life());

	SetTextColor(_hdc, RGB(255, 255, 255));
	SetBkMode(_hdc, TRANSPARENT);

	TextOut(_hdc, score_Rect.left, score_Rect.top, score, lstrlen(score));
	TextOut(_hdc, coin_Rect.left, coin_Rect.top, coin, lstrlen(coin));
	TextOut(_hdc, life_Rect.left, life_Rect.top, life, lstrlen(life));
}

void CStage::Set_Player_To_SavePoint()
{
	if (savePoint.empty())
		return; 

	CObjMgr::Get_Instance()->Set_Player_Init();
	CObjMgr::Get_Instance()->Set_Player_Jump(false);
	CObjMgr::Get_Instance()->Set_Player_Pos(savePoint.front().x + PLAYER_POS_X, PLAYER_POS_Y);
	CScrollMgr::Get_Instance()->Init_ScrollX(-savePoint.front().x);
}

void CStage::Update_SavePoint()
{
	if (savePoint.size() < 2)
		return;

	list<POINT>::iterator save = savePoint.begin();
	if ((++save)->x < (-CScrollMgr::Get_Instance()->Get_ScrollX()))
	{
		savePoint.pop_front();
	}
}

void CStage::Check_EndLine()
{
	if (endLine.x <= (-CScrollMgr::Get_Instance()->Get_ScrollX()))
	{
		isClear = true; 
	}
}

void CStage::Fall_Down()
{
	if (CObjMgr::Get_Instance()->Get_Player_RECT().bottom > WINCY)
	{
		CObjMgr::Get_Instance()->Set_Player_Die(false);
		Set_Player_To_SavePoint();
		CDataMgr::Get_Instance()->Add_Life(-1);	
	}
}

void CStage::Init_Ui()
{
	score_Rect.left = 100;
	score_Rect.right = 150;
	score_Rect.top= 50;
	score_Rect.bottom = 100;

	coin_Rect.left = 200;
	coin_Rect.right = 250;
	coin_Rect.top = 50;
	coin_Rect.bottom = 100;

	life_Rect.left = 300;
	life_Rect.right = 350;
	life_Rect.top = 50;
	life_Rect.bottom = 100;

	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Cascadia Mono SemiBold")); // 폰트 제작
}
