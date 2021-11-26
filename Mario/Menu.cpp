#include "Menu.h"

void CMenu::Initialize()
{
	//m_DC = GetDC(g_hwnd);
	Set_GameNum(GAME::MENU);

	//���� ��ŸƮ �ݹ� �Լ� ����
	function<void()> func = bind(&CMenu::StartGame, this);
	//��ŸƮ ��ư�� �ݹ� �Լ� �ʱ�ȭ
	m_StartButton.SeButtonCallBack(300, 50, 400, 400, MENU::START, func);

	//���� ���� ��ư �ݹ� �Լ� �ʱ�ȭ
	func = bind(&CMenu::ExitGame, this);
	m_ExitButton.SeButtonCallBack(300, 50, 400, 500, MENU::EXIT, func);
}

void CMenu::Update()
{
	//��ư Ŭ���� �Լ� ȣ�� �׽�Ʈ
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
	 // ��Ʈ ����
	m_DC = hDC;

	Rectangle(hDC, 0, 0, WINCX, WINCY);
	
	hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Comic Sans MS")); // ��Ʈ ����
	oldFont = (HFONT)SelectObject(hDC, hFont); // ��Ʈ ����
	
	SetTextColor(hDC, RGB(219, 0, 0)); // �ؽ�Ʈ �� ����
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
