#include "framework.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
}

void CMyBitmap::Load_Bmp(const TCHAR* pFilePath)
{
	HDC			hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);
	m_hBitBmp = (HBITMAP)LoadImage(NULL,pFilePath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION); 

	if (nullptr == m_hBitBmp)
	{
		MessageBox(g_hWnd, L"로드 실패", L"실패", MB_OK);
		return;
	}
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitBmp);

}

void CMyBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitBmp);
	DeleteDC(m_hMemDC);
}
