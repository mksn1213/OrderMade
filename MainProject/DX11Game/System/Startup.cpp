/**
*
* @file		Startup.cpp
* @brief	スタート関数実装
* @author	SHONOSUKE MAKITA
* @date		2021/01/15	実装開始
*
*/

/** インクルード部 */
#include <System/Main.h>
#include <System/Defines.h>
#include <System/resource.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")

/** プロトタイプ宣言 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);

/** グローバル変数 */
HWND		g_hWnd;			// メイン ウィンドウ ハンドル
HINSTANCE	g_hInst;		// インスタンス ハンドル
int			g_nCountFPS;	// FPSカウンタ

/**
* @brief	メイン関数
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 未使用宣言
	UNREFERENCED_PARAMETER(lpCmdLine);		// 未使用宣言

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

	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		MessageBox(NULL, ("COMの初期化に失敗しました。"), ("error"), MB_OK);
		return -1;
	}

	// インスタンス ハンドル保存
	g_hInst = hInstance;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域サイズからウィンドウ サイズ算出
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION
		| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// ウィンドウの作成
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// ウィンドウの左座標
		CW_USEDEFAULT,		// ウィンドウの上座標
		rc.right - rc.left,	// ウィンドウ横幅
		rc.bottom - rc.top,	// ウィンドウ縦幅
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectXの初期化
	if (FAILED(Init(g_hWnd))) 
	{
		return -1;
	}

	// 乱数の種を初期化
	srand((unsigned int)time(NULL));

	// メッセージループ
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) {	// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
				dwExecLastTime = dwCurrentTime;
				// 更新処理
				Update();
				// 描画処理
				Draw();
				dwFrameCount++;
			}
		}
	}

	// タイマ設定を元に戻す
	timeEndPeriod(1);

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM終了処理
	CoUninitialize();

	return (int)msg.wParam;
}


/**
* @brief	プロシージャ
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
* @brief	WM_CREATEメッセージハンドラ
*/
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
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

	// IME無効化
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1を返すとCreateWindow[Ex]が失敗する.
}


/**
* @brief	FPSカウント取得
* @return	int		FPSカウント
*/
int GetFPSCount()
{
	return g_nCountFPS;
}


/**
* @brief	インスタンスハンドル取得
*/
HINSTANCE GetInstance()
{
	return g_hInst;
}


/**
* @brief	メインウィンドウハンドル取得
*/
HWND GetMainWnd()
{
	return g_hWnd;
}