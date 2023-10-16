#define TIMER_ID 1
#define TIMER_DELAY 16
//#define DEBUG
#ifdef UNICODE
#ifdef DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#else
#ifdef DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isKeyPressed = 0;

RECT rect_user = { 5, 5, 10, 10 }; // ���� ��� ��ǥ (5, 5)���� ������ �ϴ� ��ǥ (10, 10)������ �簢��
RECT rect_target = { 50, 50, 150, 150 }; // ���� ��� ��ǥ (50, 50)���� ������ �ϴ� ��ǥ (150, 150)������ �簢��

RECT text_rect = { 10, 10, 100, 20 };
int isInside = 0;//��� �簢���� ��ǥ �簢�� �ȿ� �ִ��� ���θ� ��Ÿ���� �÷���

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);

	HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));
	const wchar_t* text = L"Crash!!!";

	static BOOL isMoving = FALSE;
	static int moveDirectionX = 0;
	static int moveDirectionY = 0;

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (!isMoving)
		{
			isMoving = TRUE;
			SetTimer(hwnd, TIMER_ID, TIMER_DELAY, NULL);
		}

		if (wParam == VK_RIGHT)
		{
			moveDirectionX = 1;
			moveDirectionY = 0;
		}
		else if (wParam == VK_LEFT)
		{
			moveDirectionX = -1;
			moveDirectionY = 0;
		}
		else if (wParam == VK_UP)
		{
			moveDirectionX = 0;
			moveDirectionY = -1;
		}
		else if (wParam == VK_DOWN)
		{
			moveDirectionX = 0;
			moveDirectionY = 1;
		}
		break;

	case WM_KEYUP:
		KillTimer(hwnd, TIMER_ID);
		isMoving = FALSE;
		break;

	case WM_TIMER:
		if (isMoving)
		{
			// ����� �簢���� ���ο� ��ġ ���
			int newLeft = rect_user.left + moveDirectionX;
			int newRight = rect_user.right + moveDirectionX;
			int newTop = rect_user.top + moveDirectionY;
			int newBottom = rect_user.bottom + moveDirectionY;

			// �� ��ġ�� ������ ��� ���� �ִ��� Ȯ��
			RECT windowRect;
			GetClientRect(hwnd, &windowRect);

			if (newLeft >= 0 && newRight <= windowRect.right && newTop >= 0 && newBottom <= windowRect.bottom)
			{
				// ��� ���� ���� ���� ����� �簢���� ��ġ ������Ʈ
				rect_user.left = newLeft;
				rect_user.right = newRight;
				rect_user.top = newTop;
				rect_user.bottom = newBottom;

				// ����� �簢���� ��ǥ �簢�� ���� �ִ��� Ȯ��
				isInside = rect_user.top >= rect_target.top && rect_user.bottom <= rect_target.bottom &&
					rect_user.left >= rect_target.left && rect_user.right <= rect_target.right;

				// ������ �ٽ� �׸���
				InvalidateRect(hwnd, NULL, TRUE);
				UpdateWindow(hwnd);
			}
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &rect_target, hBrush_target);
		FillRect(hdc, &rect_user, hBrush_user);

		if (isInside) {
			TextOut(hdc, text_rect.left, text_rect.top, text, lstrlen(text));
		}

		EndPaint(hwnd, &ps);
	}
	break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	DeleteObject(hBrush_user);
	DeleteObject(hBrush_target);
	DeleteObject(hBrush_eraser);
	ReleaseDC(hwnd, hdc);

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207038 �賲��"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// â ǥ��.
	ShowWindow(hwnd, SW_SHOW); // â ǥ��
	UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.



	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	// �޽��� ó��.
	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			// �޽��� ����
			TranslateMessage(&msg);
			// �޽����� ó��
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//���� �޽��� ������
	return (int)msg.wParam;

}