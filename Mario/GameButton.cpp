#include "framework.h"
#include "GameButton.h"
#include "CollisionMgr.h"

CGameButton::CGameButton()

{
}

CGameButton::~CGameButton()
{
}

void CGameButton::Initialize(void)
{
}

int CGameButton::Update(void)
{
	Update_Rect();
	return 0;
}

void CGameButton::Late_Update(void)
{
}

void CGameButton::Render(HDC hDC)
{
	TCHAR szBuff[32] = L"";
	HFONT		hFont, oldFont; // 폰트 설정
	HBRUSH		brush = NULL; // 색 설정

	hFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Comic Sans MS")); // 폰트 제작
	oldFont = (HFONT)SelectObject(hDC, hFont); // 폰트 변경
	//이미지?/렉텡글 출력
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	//문자 출력
	switch (m_eType)
	{
	case MENU::START:
		swprintf_s(szBuff, L"START");
		break;

	case MENU::EXIT:
		swprintf_s(szBuff, L"EXIT");
		break;
	}
		TextOut(hDC, m_tInfo.fX - 32.f, m_tInfo.fY - 17.f, szBuff, lstrlen(szBuff));
}

void CGameButton::Release(void)
{
}

void CGameButton::SetupButton(float fWidth, float fHeight, float fX,float fY, MENU::KIND _eKind)
{
	//m_tInfo.fCX = fWidth;
	//m_tInfo.fY = fHeight;
	//m_tInfo.fX = fX;
	//m_tInfo.fY = fY;


	//switch (_eKind)
	//{
	//case MENU::START:
	//	//m_pMenu->StartGame();
	//	break;
	//case MENU::EXIT:
	//	//menu->ExitGame();
	//	break;
	//}
}

void CGameButton::SeButtonCallBack(float fWidth, float fHeight, float fX, float fY, MENU::KIND _eKind, std::function<void()> _func)
{
	m_tInfo.fCX = fWidth;
	m_tInfo.fCY = fHeight;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_eType = _eKind;

	m_callBack = _func;
}

void CGameButton::OnClick()
{
	if(m_callBack != nullptr && CCollisionMgr::Collision_Mouse(this))
		m_callBack();
}
