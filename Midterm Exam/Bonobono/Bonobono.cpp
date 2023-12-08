#include <windows.h>


bool isBoxVisible = false;
bool isCircleVisible = false;
bool isBonobonoVisible = false;
bool isRyanVisible = false;
bool isCubeVisible = false;
bool isSpacebar = false;
RECT drawingRect;

void DrawBox(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBoxVisible) {

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 300, 50, 500, 200);
        DeleteObject(hBrush);
    }
}

void DrawBonobono(HWND hWnd, HDC hdc, int blink) {

    HBRUSH blueBrush = CreateSolidBrush(RGB(127, 200, 255));
    SelectObject(hdc, blueBrush);
    int centerX = (drawingRect.left + drawingRect.right) / 2;
    int centerY = (drawingRect.top + drawingRect.bottom) / 2;
    int radius = min((drawingRect.right - drawingRect.left) / 2, (drawingRect.bottom - drawingRect.top) / 2);
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    DeleteObject(blueBrush);

    HBRUSH mouseBrush = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, mouseBrush);
    Ellipse(hdc, centerX - 25, centerY, centerX + 25, centerY + 80);
    DeleteObject(mouseBrush);

    HBRUSH whitenose1Brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, whitenose1Brush);
    Ellipse(hdc, centerX - 50, centerY, centerX, centerY + 40);
    DeleteObject(whitenose1Brush);

    HBRUSH whitenose2Brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, whitenose2Brush);
    Ellipse(hdc, centerX, centerY, centerX + 50, centerY + 40);
    DeleteObject(whitenose2Brush);

    HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, noseBrush);
    Ellipse(hdc, centerX - 20, centerY - 20, centerX + 20, centerY + 20);
    DeleteObject(noseBrush);
    if (blink==0) {
        HBRUSH spaceeyeBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, spaceeyeBrush);
        MoveToEx(hdc, centerX - 110, centerY - 20, NULL);
        LineTo(hdc, centerX - 130, centerY - 40);
        MoveToEx(hdc, centerX - 110, centerY - 20, NULL);
        LineTo(hdc, centerX - 130, centerY);
        MoveToEx(hdc, centerX + 110, centerY - 20, NULL);
        LineTo(hdc, centerX + 130, centerY - 40);
        MoveToEx(hdc, centerX + 110, centerY - 20, NULL);
        LineTo(hdc, centerX + 130, centerY);
        DeleteObject(spaceeyeBrush);
    }
    else {
        HBRUSH eye1Brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, eye1Brush);
        Ellipse(hdc, centerX - 120, centerY - 20, centerX - 110, centerY);
        DeleteObject(eye1Brush);

        HBRUSH eye2Brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, eye2Brush);
        Ellipse(hdc, centerX + 110, centerY - 20, centerX + 120, centerY);
        DeleteObject(eye2Brush);

        HBRUSH whiteeye1Brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, whiteeye1Brush);
        Ellipse(hdc, centerX - 117, centerY - 16, centerX - 112, centerY - 8);
        DeleteObject(whiteeye1Brush);

        HBRUSH whiteeye2Brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, whiteeye2Brush);
        Ellipse(hdc, centerX + 112, centerY - 16, centerX + 117, centerY - 8);
        DeleteObject(whiteeye2Brush);
    }

    HBRUSH mustacheBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, mustacheBrush);
    MoveToEx(hdc, centerX - 30, centerY + 15, NULL);
    LineTo(hdc, centerX - 70, centerY + 5);
    MoveToEx(hdc, centerX - 30, centerY + 25, NULL);
    LineTo(hdc, centerX - 70, centerY + 40);
    MoveToEx(hdc, centerX + 30, centerY + 15, NULL);
    LineTo(hdc, centerX + 70, centerY + 5);
    MoveToEx(hdc, centerX + 30, centerY + 25, NULL);
    LineTo(hdc, centerX + 70, centerY + 40);
    DeleteObject(mustacheBrush);

}



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
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HBRUSH boxBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));

        FrameRect(hdc, &clientRect, boxBrush);
        FrameRect(hdc, &drawingRect, boxBrush);
        FillRect(hdc, &drawingRect, white);

        if (isBonobonoVisible) {
            DrawBonobono(hWnd, hdc, 1);
        }
        if (isSpacebar) {
            DrawBonobono(hWnd, hdc, 0);
        }

        if (isBonobonoVisible && !isSpacebar) {
            DrawBonobono(hWnd, hdc, 1);
        }

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
        L"ButtonWindowClass", L"202207038 김남규", WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME),
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