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

	// hDC 호환되는 dc를 할당하는 함수
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	// 경로로부터 이미지 파일을 읽어들이는 함수
	m_hBitBmp = (HBITMAP)LoadImage(NULL,		// 인스턴스틔 핸들, 파일로부터 읽어들이기 때문에 NULL
								pFilePath,		// 파일의 경로
								IMAGE_BITMAP,	// 어떤 타입을 읽어올지 결정하는 플래그
								0,				//	가로 사이즈 
								0,				//  세로 사이즈(어차피 이미지 파일을 그대로 읽어들일 것이기 때문에 직접 사이즈를 지정할 필요가 없다)
								LR_LOADFROMFILE | LR_CREATEDIBSECTION); //LR_LOADFROMFILE : 파일에서 이미지를 불러들임 | 읽어온 파일을 DIBSECTION형태로 변환

	if (nullptr == m_hBitBmp)
	{
		MessageBox(g_hWnd, L"로드 실패", L"실패", MB_OK);
		return;
	}
	// 준비한 DC의 GDI 오브젝트에 불러온 비트맥을 선택하기 위해 사용하는 함수
	// SelectObject GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitBmp);

}

void CMyBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);

	// 현재 dc에 선택된 gdi 오브젝트는 해제할 수 없다.
	// 현재 사용하고 있는 객체를 함부로 삭제하도록 내버려 둘 수 없기 때문에 생긴 안전 장치 역할을 하는 규정
	// 해제하기 위해 기존에 사용하던 gdi 오브젝트를 교체하고, 삭제를 진행

	DeleteObject(m_hBitBmp);
	DeleteDC(m_hMemDC);
}
