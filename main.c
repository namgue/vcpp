#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

// Drawing start point
POINT startDrawingPoint;
BOOL isDrawing = FALSE; // Drawing mode flag
BOOL isMoving = FALSE;  // Moving mode flag
HWND hwnd;              // Window handle
HBRUSH redBrush, whiteBrush; // Red and white brushes

int moveOffsetX, moveOffsetY;  // Offset for moving the drawing
int lastRectStartX, lastRectStartY, lastRectEndX, lastRectEndY; // Coordinates of the last drawn rectangle

// Window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    if (uMsg == WM_CREATE) {
        // Initialization
        whiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // Create a white brush
        redBrush = CreateSolidBrush(RGB(255, 0, 0));      // Create a red brush
        isMoving = FALSE;
        isDrawing = FALSE;
        moveOffsetX = 0;
        moveOffsetY = 0;
        lastRectStartX = 0;
        lastRectStartY = 0;
        lastRectEndX = 0;
        lastRectEndY = 0;
    }
    else if (uMsg == WM_LBUTTONDOWN) {
        // Start drawing when the left mouse button is clicked
        isDrawing = TRUE;
        startDrawingPoint.x = LOWORD(lParam);
        startDrawingPoint.y = HIWORD(lParam);
    }
    else if (uMsg == WM_LBUTTONUP) {
        if (isDrawing) {
            // End drawing when the left mouse button is released
            isDrawing = FALSE;
            int endX = LOWORD(lParam);
            int endY = HIWORD(lParam);
            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, whiteBrush);
            SetROP2(hdc, R2_WHITE);
            Rectangle(hdc, lastRectStartX, lastRectStartY, lastRectEndX, lastRectEndY);
            SetROP2(hdc, R2_COPYPEN);
            SelectObject(hdc, redBrush); // Change to red brush
            Rectangle(hdc, startDrawingPoint.x, startDrawingPoint.y, endX, endY);
            ReleaseDC(hwnd, hdc);
            lastRectStartX = startDrawingPoint.x;
            lastRectStartY = startDrawingPoint.y;
            lastRectEndX = endX;
            lastRectEndY = endY;
        }
    }
    else if (uMsg == WM_RBUTTONDOWN) {
        if (LOWORD(lParam) >= lastRectStartX && LOWORD(lParam) <= lastRectEndX &&
            HIWORD(lParam) >= lastRectStartY && HIWORD(lParam) <= lastRectEndY) {
            // Switch to moving mode when the right mouse button is clicked inside the rectangle
            isMoving = TRUE;
            moveOffsetX = LOWORD(lParam) - lastRectStartX;
            moveOffsetY = HIWORD(lParam) - lastRectStartY;
        }
    }
    else if (uMsg == WM_RBUTTONUP) {
        // End moving mode when the right mouse button is released
        isMoving = FALSE;
    }
    else if (uMsg == WM_MOUSEMOVE) {
        if (isDrawing) {
            // Draw the rectangle when in drawing mode and the mouse is moved
            int nowX = LOWORD(lParam);
            int nowY = HIWORD(lParam);
            HDC hdc = GetDC(hwnd);
            SetROP2(hdc, R2_COPYPEN);
            Rectangle(hdc, startDrawingPoint.x, startDrawingPoint.y, nowX, nowY);
            SetROP2(hdc, R2_NOTXORPEN);
            SelectObject(hdc, redBrush); // Change to red brush
            Rectangle(hdc, startDrawingPoint.x, startDrawingPoint.y, nowX, nowY);
            ReleaseDC(hwnd, hdc);
        }
        else if (isMoving && (wParam & MK_RBUTTON)) {
            // Move the rectangle when in moving mode and the right mouse button is held
            int newX = LOWORD(lParam) - moveOffsetX;
            int newY = HIWORD(lParam) - moveOffsetY;
            int width = lastRectEndX - lastRectStartX;
            int height = lastRectEndY - lastRectStartY;
            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, whiteBrush);
            SetROP2(hdc, R2_WHITE);
            Rectangle(hdc, lastRectStartX, lastRectStartY, lastRectEndX, lastRectEndY);
            SetROP2(hdc, R2_COPYPEN);
            SelectObject(hdc, redBrush); // Change to red brush
            Rectangle(hdc, newX, newY, newX + width, newY + height);
            ReleaseDC(hwnd, hdc);
            lastRectStartX = newX;
            lastRectStartY = newY;
            lastRectEndX = newX + width;
            lastRectEndY = newY + height;
        }
    }
    else if (uMsg == WM_DESTROY) {
        // Quit when the window is destroyed
        PostQuitMessage(0);
    }
    else {
        // Default handling
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return result;
}

// Entry point
#ifdef UNICODE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
#endif
{
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));

    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("MyDrawingApp"); // Window class name
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   // Cursor
    wc.style = CS_HREDRAW | CS_VREDRAW; // Window style
    wc.lpfnWndProc = WindowProc; // Window procedure function

    if (RegisterClass(&wc) == 0) {
        // Exit on failure to register window class
        exit(-1);
    }

    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202207038 ±è³²±Ô"), // Window title
        WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME), // Window style
        0, 0, 800, 600, // Window position and size
        NULL, NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        // Exit on failure to create window
        exit(-1);
    }

    ShowWindow(hwnd, nCmdShow); // Show the window
    UpdateWindow(hwnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT) {
        if (GetMessage(&msg, hwnd, 0, 0)) {
            TranslateMessage(&msg); // Translate keyboard input
            DispatchMessage(&msg);  // Dispatch messages
        }
    }

    return 0;
}
