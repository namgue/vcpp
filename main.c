#include <windows.h>

// 윈도우 핸들 전역 변수
HWND g_hWnd;

// 그림 그리기 시작점과 그리기 중인지 여부
POINT g_StartPoint;
BOOL g_IsDrawing = FALSE;

// 그림 이동 중인지 여부
BOOL g_IsMoving = FALSE;
int g_MoveOffsetX = 0;
int g_MoveOffsetY = 0;

// 마지막으로 그린 사각형의 좌표
int g_LastDrawStartX = 0;
int g_LastDrawStartY = 0;
int g_LastDrawEndX = 0;
int g_LastDrawEndY = 0;

// 브러시 변수
HBRUSH g_RedBrush;
HBRUSH g_WhiteBrush;

// 윈도우 프로시저 함수 선언
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 윈도우 등록 및 생성 함수
BOOL InitializeWindow(HINSTANCE hInstance, int nCmdShow);

// 그림 그리기 함수
void DrawRectangle(HDC hdc, int startX, int startY, int endX, int endY);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    if (!InitializeWindow(hInstance, nCmdShow)) {
        return -1;
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, g_hWnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

BOOL InitializeWindow(HINSTANCE hInstance, int nCmdShow) {
    // 윈도우 클래스 등록
    WNDCLASS wc = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyDrawingAppClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        return FALSE;
    }

    // 윈도우 생성
    g_hWnd = CreateWindow(
        L"MyDrawingAppClass", L"202207038 김남규",
        WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME),
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (!g_hWnd) {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    // 브러시 생성
    g_RedBrush = CreateSolidBrush(RGB(255, 0, 0));
    g_WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

    return TRUE;
}

void DrawRectangle(HDC hdc, int startX, int startY, int endX, int endY) {
    Rectangle(hdc, startX, startY, endX, endY);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    switch (uMsg) {
    case WM_LBUTTONDOWN:
        g_IsDrawing = TRUE;
        g_StartPoint.x = LOWORD(lParam);
        g_StartPoint.y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP:
        if (g_IsDrawing) {
            g_IsDrawing = FALSE;
            int endX = LOWORD(lParam);
            int endY = HIWORD(lParam);
            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, g_WhiteBrush);
            SetROP2(hdc, R2_WHITE);
            DrawRectangle(hdc, g_LastDrawStartX, g_LastDrawStartY, g_LastDrawEndX, g_LastDrawEndY);
            SetROP2(hdc, R2_COPYPEN);
            SelectObject(hdc, g_RedBrush);
            DrawRectangle(hdc, g_StartPoint.x, g_StartPoint.y, endX, endY);
            ReleaseDC(hwnd, hdc);
            g_LastDrawStartX = g_StartPoint.x;
            g_LastDrawStartY = g_StartPoint.y;
            g_LastDrawEndX = endX;
            g_LastDrawEndY = endY;
        }
        break;

    case WM_RBUTTONDOWN:
        if (LOWORD(lParam) >= g_LastDrawStartX && LOWORD(lParam) <= g_LastDrawEndX &&
            HIWORD(lParam) >= g_LastDrawStartY && HIWORD(lParam) <= g_LastDrawEndY) {
            g_IsMoving = TRUE;
            g_MoveOffsetX = LOWORD(lParam) - g_LastDrawStartX;
            g_MoveOffsetY = HIWORD(lParam) - g_LastDrawStartY;
        }
        break;

    case WM_RBUTTONUP:
        g_IsMoving = FALSE;
        break;

    case WM_MOUSEMOVE:
        if (g_IsDrawing) {
            int nowX = LOWORD(lParam);
            int nowY = HIWORD(lParam);
            HDC hdc = GetDC(hwnd);
            SetROP2(hdc, R2_COPYPEN);
            DrawRectangle(hdc, g_StartPoint.x, g_StartPoint.y, nowX, nowY);
            SetROP2(hdc, R2_NOTXORPEN);
            SelectObject(hdc, g_RedBrush);
            DrawRectangle(hdc, g_StartPoint.x, g_StartPoint.y, nowX, nowY);
            ReleaseDC(hwnd, hdc);
        }
        else if (g_IsMoving && (wParam & MK_RBUTTON)) {
            int newX = LOWORD(lParam) - g_MoveOffsetX;
            int newY = HIWORD(lParam) - g_MoveOffsetY;
            int width = g_LastDrawEndX - g_LastDrawStartX;
            int height = g_LastDrawEndY - g_LastDrawStartY;
            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, g_WhiteBrush);
            SetROP2(hdc, R2_WHITE);
            DrawRectangle(hdc, g_LastDrawStartX, g_LastDrawStartY, g_LastDrawEndX, g_LastDrawEndY);
            SetROP2(hdc, R2_COPYPEN);
            SelectObject(hdc, g_RedBrush);
            DrawRectangle(hdc, newX, newY, newX + width, newY + height);
            ReleaseDC(hwnd, hdc);
            g_LastDrawStartX = newX;
            g_LastDrawStartY = newY;
            g_LastDrawEndX = newX + width;
            g_LastDrawEndY = newY + height;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }

    return result;
}
