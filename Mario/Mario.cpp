﻿
#include "framework.h"
#include "Mario.h"
#include "Include.h"
#include "Game.h"
#include "Menu.h"
#include "Stage1.h"
#include "Manager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MARIO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MARIO));

    MSG msg;
    HDC m_hdc = nullptr;	// main DC 
    HDC m_hdcBuff = nullptr;	// Buffer DC 
    HBITMAP m_hbmpBuff = nullptr;	// Buffer DC HBITMAP 
    HBITMAP m_hbmpBuffOld = nullptr;	// 기존 Buffer DC HBITMAP 

    msg.message = WM_NULL;

    DWORD dwOldTime = GetTickCount();
    CGame* game = nullptr;
    GAME::ID stageNum = GAME::MENU;

    // 기본 메시지 루프입니다.
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (dwOldTime + 10 < GetTickCount())
            {
                if (!game)
                {
                    switch (stageNum)
                    {
                    case GAME::MENU:
                        game = new CMenu;
                        break;
                    case GAME::STAGEONE:
                        game = new CStage1;
                        break;
                    case GAME::ID_END:
                        ReleaseDC(g_hWnd, m_hdc);
                        Safe_Delete(game);
                        CObjMgr::Get_Instance()->Destroy_Instance();
                        CObjPoolMgr::Get_Instance()->Release();
                        CObjPoolMgr::Get_Instance()->Destroy_Instance();
                        CScrollMgr::Get_Instance()->Destroy_Instance();
                        CDataMgr::Get_Instance()->Destroy_Instance(); 
                        CLineMgr::Get_Instance()->Destroy_Instance(); 
                        CBmpMgr::Get_Instance()->Destroy_Instance();
                        CKeyMgr::Get_Instance()->Destroy_Instance();
                        PostQuitMessage(0);
                        return (int)msg.wParam;
					default:
						game = new CMenu;
						stageNum = GAME::MENU;
						break;
                    /*case GAME::STAGETWO:
                        break; 
                    case GAME::STAGETHREE:
                        break; 
                    case GAME::STAGEFOUR:
                        break;*/
                    }
                    game->Initialize();
                }

                m_hdc = GetDC(g_hWnd); // 보여지는 DC 
                m_hdcBuff = CreateCompatibleDC(m_hdc); // 더블 버퍼링에 사용될 DC 만들기 
                m_hbmpBuff = CreateCompatibleBitmap(m_hdc, WINCX,WINCY); // m_hdcBuff의 HBITMAP 만들기 
                m_hbmpBuffOld = (HBITMAP)::SelectObject(m_hdcBuff, m_hbmpBuff);

                game->Update();
                game->Late_Update();
                game->Render(m_hdcBuff);
                //_crtBreakAlloc = 209;

                BitBlt(m_hdc, 0, 0, WINCX, WINCY, m_hdcBuff, 0, 0, SRCCOPY);

                SelectObject(m_hdcBuff, m_hbmpBuffOld);	// 기존 HBITMAP 선택 
                DeleteObject(m_hbmpBuff); // 만든 HBITMAP 지움 
                DeleteDC(m_hdcBuff); // Buffer 지움 
               
                dwOldTime = GetTickCount();
                if (game->Get_GameNum() != stageNum)
                {
					stageNum = game->Get_GameNum();
                    game->Release();
                    Safe_Delete(game);
                    ReleaseDC(g_hWnd, m_hdc);
                }
            }
        }
    }
    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MARIO));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    RECT		rc = { 0,0, WINCX, WINCY };

    // 최종적인 윈도우 렉트 창 설정 = rc 사이즈 + 윈도우 기본 창 사이즈 + 메뉴 바 크기 고려
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        rc.right - rc.left,
        rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    g_hWnd = hWnd;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다.
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        //KillTimer(hWnd, 0); // settimer로 발생한 타이머를 삭제하는 용도
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
