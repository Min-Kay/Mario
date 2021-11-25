#include "Stage.h"

void CStage::Set_Result()
{
}

void CStage::Result()
{
	switch (m_result) {
	case GAME::WIN:
		Show_Win_Lose();
		Set_GameNum(GAME::ID((int)m_GameNum + 1));
		break;
	case GAME::LOSE:
		Show_Win_Lose();
		Set_GameNum(GAME::MENU);
		break;
	}
}

void CStage::Show_Win_Lose()
{
	{
		DWORD		showTime = GetTickCount();
		TCHAR		szShow[10] = L"";
		RECT		m_BackgroundRect{ 0,0,WINCX,WINCY }, m_TextRect{ WINCX / 2 - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2) };
		HFONT		hFont, oldFont; // 폰트 설정
		HBRUSH		brush = NULL; // 색 설정

		hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림체")); // 폰트 제작
		oldFont = (HFONT)SelectObject(m_DC, hFont); // 폰트 변경

		switch (m_result)
		{
		case GAME::WIN:
			SetTextColor(m_DC, RGB(0, 255, 0)); // 텍스트 색 설정
			brush = CreateSolidBrush(RGB(0, 150, 0)); // 배경 색 설정
			swprintf_s(szShow, L"승리");
			break;
		case GAME::LOSE:
			SetTextColor(m_DC, RGB(255, 0, 0));
			brush = CreateSolidBrush(RGB(150, 0, 0));
			swprintf_s(szShow, L"패배");
			break;
		default:
			break;
		}

		Rectangle(m_DC, m_BackgroundRect.left, m_BackgroundRect.top, m_BackgroundRect.right, m_BackgroundRect.bottom);

		FillRect(m_DC, &m_BackgroundRect, brush); // RECT에 색 채우기 
		FillRect(m_DC, &m_TextRect, brush);

		while (showTime + 3000 > GetTickCount())
		{
			TextOut(m_DC, m_TextRect.left, m_TextRect.top, szShow, lstrlen(szShow));
		}
	}
}
