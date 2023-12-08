#include "yuhanCG.h"

bool isBoxVisible = false;
bool isCircleVisible = false;
bool isBonobonoVisible = false;
bool isRyanVisible = false;
bool isCubeVisible = false;
bool isSpacebar = false;
bool isDragging = false;
bool isMoving = false;

RECT drawingRect;
POINT dragpoint;
POINT movepoint;
POINT endpoint;
RECT currentRect = { 0, 0, 0, 0 };
POINT clickPoint;
RECT copiedRect = { 0, 0, 0, 0 };


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    RECT clientRect = { 8, 8, 792, 472 };
    drawingRect = { 16, 112, 784, 464 };

    switch (message) {
    case WM_COMMAND: {
        isBoxVisible = false;
        isCircleVisible = false;
        isBonobonoVisible = false;
        isRyanVisible = false;
        isCubeVisible = false;


        if (LOWORD(wParam) == 1) {
            isBoxVisible = true;
        }
        else if (LOWORD(wParam) == 2) {
            isCircleVisible = true;
        }
        else if (LOWORD(wParam) == 3) {
            isBonobonoVisible = true;
        }
        else if (LOWORD(wParam) == 4) {
            isRyanVisible = true;
        }
        else if (LOWORD(wParam) == 5) {
            isCubeVisible = true;
        }

        dragpoint = { 0, 0 };
        endpoint = { 0, 0 };

        InvalidateRect(hWnd, NULL, TRUE);
        SetFocus(hWnd);
        break;
    }
    case WM_KEYDOWN:
    {
        if (wParam == VK_SPACE) {
            isSpacebar = true;
            if (isBonobonoVisible) {
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        break;
    }
    case WM_KEYUP:
    {
        isSpacebar = false;
        if (isBonobonoVisible) {
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }

    case WM_LBUTTONDOWN:
    {
        if (isRyanVisible || isBoxVisible || isCircleVisible || isCubeVisible) {
            dragpoint.x = LOWORD(lParam);
            dragpoint.y = HIWORD(lParam);
            isDragging = true;
        }
        break;
    }

    case WM_RBUTTONDOWN:
    {
        if (isBoxVisible||isCubeVisible) {
            clickPoint.x = LOWORD(lParam);
            clickPoint.y = HIWORD(lParam);
            if (PtInRect(&currentRect, clickPoint)) {
                copiedRect = currentRect;
                isMoving = true;
            }
        }
        break;
    }

    case WM_MOUSEMOVE:
    {
        if (isDragging) {
            HDC hdc = GetDC(hWnd);

            endpoint.x = LOWORD(lParam);
            endpoint.y = HIWORD(lParam);

            if (PtInRect(&drawingRect, endpoint)) {
                int dragRectLeft = dragpoint.x;
                int dragRectTop = dragpoint.y;
                int dragRectRight = endpoint.x;
                int dragRectBottom = endpoint.y;

                InvalidateRect(hWnd, &drawingRect, TRUE);
                UpdateWindow(hWnd);
                if (isRyanVisible) {
                    DrawRyan(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
                }
                if (isCircleVisible)
                {
                    DrawCircle(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
                }
                if (isBoxVisible)
                {
                    DrawBox(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);

                }
                if (isCubeVisible) {
                    DrawCube(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
                }
            }
            else {
                isDragging = false;
            }
            ReleaseDC(hWnd, hdc);
        }else if(isMoving) {
            HDC hdc = GetDC(hWnd);

            movepoint.x = LOWORD(lParam);
            movepoint.y = HIWORD(lParam);

            if (PtInRect(&drawingRect, dragpoint)) {
                if (PtInRect(&drawingRect, endpoint)) {
                    dragpoint.x = copiedRect.left + (movepoint.x - clickPoint.x);
                    dragpoint.y = copiedRect.top + (movepoint.y - clickPoint.y);
                    endpoint.x = copiedRect.right + (movepoint.x - clickPoint.x);
                    endpoint.y = copiedRect.bottom + (movepoint.y - clickPoint.y);

                    InvalidateRect(hWnd, &drawingRect, TRUE);
                    UpdateWindow(hWnd);

                    if (isBoxVisible)
                    {
                        DrawBox(hWnd, hdc, dragpoint.x, dragpoint.y, endpoint.x, endpoint.y);
                    }
                    if (isCubeVisible) {
                        DrawCube(hWnd, hdc, dragpoint.x, dragpoint.y, endpoint.x, endpoint.y);
                    }
                }
                else {
                    isMoving = false;
                }ReleaseDC(hWnd, hdc);
            }
        }
        break;
    }

    case WM_LBUTTONUP:
    {
        if (isRyanVisible || isBoxVisible || isCircleVisible || isCubeVisible) {
            isDragging = false;
        }
        break;
    }

    case WM_RBUTTONUP:
    {
        if (isBoxVisible||isCubeVisible) {
            isMoving = false;
        }
        break;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HBRUSH boxBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));

        FrameRect(hdc, &clientRect, boxBrush);
        FrameRect(hdc, &drawingRect, boxBrush);
        DeleteObject(boxBrush);
        FillRect(hdc, &drawingRect, white);
        DeleteObject(white);

        int dragRectLeft = dragpoint.x;
        int dragRectTop = dragpoint.y;
        int dragRectRight = endpoint.x;
        int dragRectBottom = endpoint.y;

        if (isBonobonoVisible) {
            DrawBonobono(hWnd, hdc, 1);
        }
        if (isSpacebar) {
            DrawBonobono(hWnd, hdc, 0);
        }

        if (isBonobonoVisible && !isSpacebar) {
            DrawBonobono(hWnd, hdc, 1);
        }

        if (isRyanVisible) {
            DrawRyan(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
        }

        if (isCircleVisible) {
            DrawCircle(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
        }
        if (isBoxVisible) {
            DrawBox(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
        }
        if (isCubeVisible) {
            DrawBox(hWnd, hdc, dragRectLeft, dragRectTop, dragRectRight, dragRectBottom);
        }

        currentRect = { dragRectLeft, dragRectTop, dragRectRight, dragRectBottom };

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_SETCURSOR:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        if (PtInRect(&drawingRect, pt)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            return TRUE;
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            return TRUE;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}




int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 240, 200)));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    RECT rect = { 150, 100, 950, 580 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"202207038 ±è³²±Ô", WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME),
        0, 0, width, height, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        32, 32, 121.6, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        185.6, 32, 121.6, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        339.2, 32, 121.6, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        492.8, 32, 121.6, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        646.4, 32, 121.6, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}