#include "Menu.h"

void CMenu::Initialize()
{
	m_DC = GetDC(g_hwnd);
	Set_GameNum(GAME::MENU);
}

void CMenu::Update()
{
}

void CMenu::Late_Update()
{
}

void CMenu::Render()
{
}

void CMenu::Release()
{
}
