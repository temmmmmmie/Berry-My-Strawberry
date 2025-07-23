#include "pch.h"
//#include <vld/vld.h>
#include "framework.h"
#include "WinAPI_56.h"

#include "Engine.h"
#include "TimeMgr.h"
#include "PathMgr.h"

HINSTANCE hInst;
HCURSOR Cursor;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK FlipBookPreview(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK FlipBookColRow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);;
int APIENTRY wWinMain(_In_     HINSTANCE hInstance,         // 실행된 프로세스 ID
                      _In_opt_ HINSTANCE hPrevInstance,     // 사용되지 않는 인자(이전 프로세스 핸들(ID))
                      _In_     LPWSTR    lpCmdLine,         
                      _In_     int       nCmdShow)
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(21798);
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    // 생성시킬 윈도우 옵션 설정
    WNDCLASSEXW wcex = {};
    wcex.lpszClassName = L"MyMind"; // 키값
    wcex.lpszMenuName = 0;//MAKEINTRESOURCEW(IDC_WINAPI56);
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // 해당 윈도우에 발생한 메세지를 처리할 함수의 주소값
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    RegisterClassExW(&wcex); // 옵션 등록

    // 윈도우 생성
    HWND hWnd = CreateWindowW(L"MyMind", L"Berry, my Strawberry", WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
       
    ShowWindow(hWnd, true);

    UpdateWindow(hWnd);

    HWND PreviewDialog = CreateDialog(hInstance, MAKEINTRESOURCE(DLG_FLIPBOOK_PREVIEW), hWnd, FlipBookPreview);
    HWND ColRowDialog = CreateDialog(hInstance, MAKEINTRESOURCE(DLG_FLIPBOOK_COLROW), hWnd, FlipBookColRow);


    // Engine 초기화
    Engine::GetInst()->Init(hInstance, hWnd, PreviewDialog, ColRowDialog, 1920, 1080);
    auto cursorpath = PathMgr::GetInst()->GetContentPath() + L"\\Cursor\\Strawberry.cur";
    Cursor = LoadCursorFromFile(cursorpath.c_str());


    // 단축키 조합정보
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI56));

    MSG msg = {};
    
    // GetMessage 함수
    // 프로세스에 발생한 이벤트(메세지)을 메세지큐에서 가져옴
    // 만약 메세지큐에 메세지가 없으면, 함수가 반환되지 않는다.
    // 메세지큐에 메세지가 있어야만, 그 메세지를 꺼내오면서 반환된다.
    // 반환값이 거짓 : 꺼내온 메세지가 WM_QUIT 인 경우

    // PeekMessage 함수
    // 프로세스에 발생한 메세지를 메세지큐에서 가져온다.
    // 메세지큐에 메세지가 있던 없던 반환된다.
    // 메시지가 있으면 True, 없으면 False
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            // 대화상자 메시지 먼저 처리
            bool handled = false;

            if (IsDialogMessage(PreviewDialog, &msg))
                handled = true;

            else if (IsDialogMessage(ColRowDialog, &msg))
                handled = true;

            else if (TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                handled = true;

            if (!handled) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // 메세지 큐에 메세지가 없는 경우
        else
        {
            // Game 구현
            // 1 프레임 수행
            // FPS (Frame Per Second, F/S)
            // FPS (First Person Shooting)
            Engine::GetInst()->Progress();
        }

    
    }
    return (int) msg.wParam;
}
LRESULT CALLBACK MenuButtonCallBack(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MenuButtonCallBackFlip(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            MenuButtonCallBack(hWnd, message, wParam, lParam);
            MenuButtonCallBackFlip(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY: // 프로세스가 보유한 윈도우중 하나라도 종료가 되는 경우
        PostQuitMessage(0); // 프로세스 종료 함수
        break;

    case WM_KEYDOWN:
    {
        if (wParam == 'W')
            int a = 0;
    }
        break;
    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(Cursor);
            return TRUE;
        }
        break;
    default:
        // 대부분의 윈도우 메세지를 처리해주는 함수
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
