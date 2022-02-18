/**
*
* @file		Startup.cpp
* @brief	�X�^�[�g�֐�����
* @author	SHONOSUKE MAKITA
* @date		2021/01/15	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Main.h>
#include <System/Defines.h>
#include <System/resource.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")

/** �v���g�^�C�v�錾 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);

/** �O���[�o���ϐ� */
HWND		g_hWnd;			// ���C�� �E�B���h�E �n���h��
HINSTANCE	g_hInst;		// �C���X�^���X �n���h��
int			g_nCountFPS;	// FPS�J�E���^

/**
* @brief	���C���֐�
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// ���g�p�錾
	UNREFERENCED_PARAMETER(lpCmdLine);		// ���g�p�錾

	HWND		hWnd;
	MSG			msg;

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINFRM)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		CLASS_NAME,
		nullptr
	};

	// COM������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		MessageBox(NULL, ("COM�̏������Ɏ��s���܂����B"), ("error"), MB_OK);
		return -1;
	}

	// �C���X�^���X �n���h���ۑ�
	g_hInst = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈�T�C�Y����E�B���h�E �T�C�Y�Z�o
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION
		| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// �E�B���h�E�̍����W
		CW_USEDEFAULT,		// �E�B���h�E�̏���W
		rc.right - rc.left,	// �E�B���h�E����
		rc.bottom - rc.top,	// �E�B���h�E�c��
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// �t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectX�̏�����
	if (FAILED(Init(g_hWnd))) 
	{
		return -1;
	}

	// �����̎��������
	srand((unsigned int)time(NULL));

	// ���b�Z�[�W���[�v
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else {
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) {	// 0.5�b���ƂɎ��s
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
				dwExecLastTime = dwCurrentTime;
				// �X�V����
				Update();
				// �`�揈��
				Draw();
				dwFrameCount++;
			}
		}
	}

	// �^�C�}�ݒ�����ɖ߂�
	timeEndPeriod(1);

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM�I������
	CoUninitialize();

	return (int)msg.wParam;
}


/**
* @brief	�v���V�[�W��
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam) 
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/**
* @brief	WM_CREATE���b�Z�[�W�n���h��
*/
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// �N���C�A���g�̈�T�C�Y��SCREEN_WIDTH�~SCREEN_HEIGHT�ɍĐݒ�.
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME������
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1��Ԃ���CreateWindow[Ex]�����s����.
}


/**
* @brief	FPS�J�E���g�擾
* @return	int		FPS�J�E���g
*/
int GetFPSCount()
{
	return g_nCountFPS;
}


/**
* @brief	�C���X�^���X�n���h���擾
*/
HINSTANCE GetInstance()
{
	return g_hInst;
}


/**
* @brief	���C���E�B���h�E�n���h���擾
*/
HWND GetMainWnd()
{
	return g_hWnd;
}