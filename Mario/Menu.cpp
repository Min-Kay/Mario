#include "Menu.h"

void CMenu::Initialize()
{
	//m_DC = GetDC(g_hwnd);
	Set_GameNum(GAME::MENU);

	//게임 스타트 콜백 함수 생성
	function<void()> func = bind(&CMenu::StartGame, this);
	//스타트 버튼에 콜백 함수 초기화
	m_StartButton.SeButtonCallBack(300, 50, 400, 400, MENU::START, func);

	//게임 종료 버튼 콜백 함수 초기화
	func = bind(&CMenu::ExitGame, this);
	m_ExitButton.SeButtonCallBack(300, 50, 400, 500, MENU::EXIT, func);
}

void CMenu::Update()
{
	//버튼 클릭시 함수 호출 테스트
	m_StartButton.Update();
	m_ExitButton.Update();
	
}

void CMenu::Late_Update()
{
	m_StartButton.OnClick();
	m_ExitButton.OnClick();
}

void CMenu::Render(HDC hDC)
{
	 // 폰트 설정
	m_DC = hDC;

	Rectangle(hDC, 0, 0, WINCX, WINCY);
	
	hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Comic Sans MS")); // 폰트 제작
	oldFont = (HFONT)SelectObject(hDC, hFont); // 폰트 변경
	
	SetTextColor(hDC, RGB(219, 0, 0)); // 텍스트 색 설정
	swprintf_s(szBuff1, L"Super");
	TextOut(hDC, fX, fY, szBuff1, lstrlen(szBuff1));

	SetTextColor(hDC, RGB(0, 0, 201));
	swprintf_s(szBuff2, L"Mario");
	TextOut(hDC, fX, fY + 100, szBuff2, lstrlen(szBuff2));
	
	SetTextColor(hDC, RGB(0, 0, 0));
	m_StartButton.Render(hDC);
	m_ExitButton.Render(hDC);
}

void CMenu::Release()
{
	ReleaseDC(g_hWnd, m_DC);
}

void CMenu::StartGame()
{
	Set_GameNum(GAME::STAGEONE);
}

void CMenu::ExitGame()
{
	PostQuitMessage(0);
}
