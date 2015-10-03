// 1410990063_PISE2.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "2_2.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ここにコードを挿入してください。
	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_2));

	// メイン メッセージ ループ:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
//  コメント:
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//    Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY2_2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1024, 768, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 選択されたメニューの解析:
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 描画コードをここに追加してください...

		int x;
		for (x = 10; x <= 100; ++x)
			SetPixel(hdc, x, 20, RGB(0, 0, 0));
		int y;
		for (y = 0; y <= 100; ++y)
			SetPixel(hdc, 55, y, RGB(0, 0, 0));

		/*
		 * 課題1
		 * for文を用いて(0, 0)から(200, 200)までの斜線を描くプログラムを作る
		 */
		{
			int i;
			for (i = 0; i <= 200; ++i) {
				SetPixel(hdc, i, i, RGB(0, 0, 0));
			}
		}

		/*
		 * 課題2
		 * 正方形を描くプログラムを作る
		 */
		{
			const int start_x = 10;  // 左上のx座標
			const int start_y = 10; // 左上のy座標
			const int end_x   = 110; // 右下のx座標
			const int end_y   = 110; // 右下のy座標
			const int ival  = 255 / (end_y - start_y); //色の間隔

			for (x = start_x; x <= end_x; ++x) {
				for (y = start_y; y <= end_y; ++y) {
					SetPixel(hdc, x, y, RGB(0, 0, 0));
				}
			}
		}

		/* 
		 * 課題3
		 * 左上(10, 110), 右下(110, 210)の正方形で隙間が1ピクセルの縦のストライプ
		 */
		{
			const int start_x = 10;  // 左上のx座標
			const int start_y = 110; // 左上のy座標
			const int end_x   = 110; // 右下のx座標
			const int end_y   = 210; // 右下のy座標
			const int ival    = 1;   // 間隔
			
			for (x = start_x; x <= end_x; x += 1 + ival) {
				for (y = start_y; y <= end_y; ++y) {
					SetPixel(hdc, x, y, RGB(0, 0, 0));
				}
			}
		}

		/*
		 * 課題4
		 * (10, 210)～(110, 310)の正方形で隙間が2画素の点線正方形
		 */
		{
			const int start_x = 10;  // 左上のx座標
			const int start_y = 210; // 左上のy座標
			const int end_x   = 110; // 右下のx座標
			const int end_y   = 310; // 右下のy座標
			const int ival    = 2;   // 間隔

			for (x = start_x; x <= end_x; x += 1 + ival) {
				for (y = start_y; y <= end_y; y += 1 + ival) {
					SetPixel(hdc, x, y, RGB(0, 0, 0));
				}
			}
		}

		/*
		 * 特別課題
		 * 課題2の正方形の右横に同じサイズの正方形
		 * ただし、色が赤->青にグラデーション
		 */
		{
			const int start_x = 110; // 左上のx座標
			const int start_y = 10;  // 左上のy座標
			const int end_x   = 210; // 右下のx座標
			const int end_y   = 110; // 右下のy座標
			const int ival    = 255 / (end_y - start_y); //色の間隔

			for (x = start_x; x <= end_x; ++x) {
				int i = 0;
				for (y = start_y; y <= end_y; ++y, ++i) {
					SetPixel(hdc, x, y,
						RGB(255 - i * ival,	0, 0 + i * ival));
				}
			}
		}

		/*
		 * 課題5
		 * (10, 310)～(110, 410)の正方形
		 * 赤　青
		 * 青  赤
		 */
		{
			const int start_x = 10;                              // 左上のx座標
			const int start_y = 310;                             // 左上のy座標
			const int end_x   = 110;                             // 右下のx座標
			const int end_y   = 410;                             // 右下のy座標
			const int mid_x   = start_x + (end_x - start_x) / 2; // 中心のx座標
			const int mid_y   = start_y + (end_y - start_y) / 2; // 中心のy座標
			COLORREF color;                                      // 色の変数
			
			for (x = start_x; x <= end_x; ++x) {
				for (y = start_y; y <= end_y; ++y) {
					if ((x < mid_x && y < mid_y) || (x > mid_x && y > mid_y)) {
						color = RGB(255, 0, 0);
					} else {
						color = RGB(0, 0, 255);
					}
					SetPixel(hdc, x, y, color);
				}
			}
		}

		/*
		 * 課題6
		 * 課題5の正方形の右横に正方形
		 * 青 青
		 * 赤 赤
		 */
		{
			const int start_x = 110;                             // 左上のx座標
			const int start_y = 310;                             // 左上のy座標
			const int end_x   = 210;                             // 右下のx座標
			const int end_y   = 410;                             // 右下のy座標
			const int mid_x   = start_x + (end_x - start_x) / 2; // 真ん中のx座標
			const int mid_y   = start_y + (end_y - start_y) / 2; // 真ん中のy座標
			const int sleep_msec = 100;                          // Sleepする秒数(ミリ秒)
			const int count = 100;                               // 繰り返す回数
			COLORREF color;                                      // 色の変数
			
			for (int i = 0; i < count; ++i) {
				for (x = start_x; x <= end_x; ++x) {
					for (y = start_y; y <= end_y; ++y) {
						if ((x < mid_x && y < mid_y) || (x > mid_x && y > mid_y)) {
							if (i % 2 == 0) {
								color = RGB(255, 0, 0);
							} else {
								color = RGB(0, 0, 255);
							}
						} else {
							if (i % 2 == 0) {
								color = RGB(0, 0, 255);
							} else {
								color = RGB(255, 0, 0);
							}
						}
						SetPixel(hdc, x, y, color);
					}
				}
				Sleep(sleep_msec);
			}
		}

	
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
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
