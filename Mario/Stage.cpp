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
	{
		DWORD		showTime = GetTickCount();
		TCHAR		szShow[10] = L"";
		RECT		m_BackgroundRect{ 0,0,WINCX,WINCY }, m_TextRect{ WINCX / 2 - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2) };
		HFONT		hFont, oldFont; // 폰트 설정
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

		while (showTime + 3000 > GetTickCount())
		{
		BitBlt(m_hdc, 0, 0, WINCX, WINCY, _hdc, 0, 0, SRCCOPY);
		}
	}
}

void CStage::Check_State()
{
	if (isClear)
	{
		Set_Result(GAME::WIN);
	}

	else if(isFail)
	{
		Set_Result(GAME::LOSE);
	}
}

void CStage::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		isClear = true;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		isFail = true;
}
