// 2_3.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "2_3.h"
#include <stdio.h>
#include <math.h>

#define MAX_LOADSTRING 100

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x > y ? y : x)

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
	LoadString(hInstance, IDC_MY2_3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_3));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2_3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_3);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
				int x, y;

		// 円を描く例題
		{
			const int a = 100; // 中心のx座標
			const int b = 100; // 中心のy座標
			const int r = 50;  // 半径

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					// 円の方程式に基づいて円を描く
					if (pow(x - a, 2.0) + pow(y - b, 2.0) == pow(r, 2.0)) {
						SetPixel(hdc, x, y, RGB(0, 0, 0));
					}
				}
			}
		}

		/**
		 * 課題1
		 * (110, 10)から(210, 110)の範囲に、接して、内部が赤く塗りつぶされた円を描く。 
		 */
		{
			const int left   = 110;                       // 描画範囲の左上のx座標
			const int top    = 10;                        // 描画範囲の左上のy座標
			const int right  = 210;                       // 描画範囲の右下のx座標
			const int bottom = 110;                       // 描画範囲の右下のy座標
			const int a      = left + (right - left) / 2; // 中心のx座標
			const int b      = top + (bottom - top) / 2;  // 中心のy座標
			const int r      = right - a;                 // 半径

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					// 中を塗りつぶすので==で辺だけを描画するのではなく、円の中も描画する
					if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
						SetPixel(hdc, x, y, RGB(255, 0, 0));
					}
				}
			}
		}

		/**
		 * 課題2
		 * (110, 210)から(210, 310)の範囲に接するドーナツ状の円を描く
		 */
		{
			const int left   = 110;                       // 描画範囲の左上のx座標
			const int top    = 210;                       // 描画範囲の左上のy座標
			const int right  = 210;                       // 描画範囲の右下のx座標
			const int bottom = 310;                       // 描画範囲の右下のy座標
			const int a      = left + (right - left) / 2; // 中心のx座標
			const int b      = top + (bottom - top) / 2;  // 中心のy座標
			const int r      = right - a;                 // 半径
			const int void_r = 25;                        // 空洞の半径（任意）

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					const double xa2 = pow(x - a, 2.0); // (x - a)^2
					const double yb2 = pow(y - b, 2.0); // (y - b)^2
					// 空洞の円の中は描写しないようにする
					if (xa2 + yb2 < pow(r, 2.0) && xa2 + yb2 >= pow(void_r, 2.0)) {
						SetPixel(hdc, x, y, RGB(0, 0, 0));
					}
				}
			}
		}

		/**
		 * 課題3
		 * (110, 310)から(210, 410)に以下の円を描く
		 * 赤　青
		 * 青　赤
		 */
		{
			const int left      = 110;                       // 描画範囲の左上のx座標
			const int top       = 310;                        // 描画範囲の左上のy座標
			const int right     = 210;                       // 描画範囲の右下のx座標
			const int bottom    = 410;                       // 描画範囲の右下のy座標
			const int a         = left + (right - left) / 2; // 中心のx座標
			const int b         = top + (bottom - top) / 2;  // 中心のy座標
			const int r         = right - a;                 // 半径
			const COLORREF red  = RGB(255, 0, 0);            // 赤
			const COLORREF blue = RGB(0, 0, 255);            // 青

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
						COLORREF col;
						// 中心から左上または、右下の場合は赤
						if ((x < a && y < b) || (x >= a && y >= b)) {
							col = red;
						} else { // そうでない場合は青
							col = blue;
						}
						SetPixel(hdc, x, y, col);
					}
				}
			}
		}

		/**
		 * 課題4（チャレンジ問題）
		 * (0, 0) ~ (100, 100)の円を(300, 0) ~ (400, 100)の円に移動
		 */
		{
			const int left      = 0;                         // 描画範囲の左上のx座標
			const int top       = 0;                         // 描画範囲の左上のy座標
			const int right     = 100;                       // 描画範囲の右下のx座標
			const int bottom    = 100;                       // 描画範囲の右下のy座標
			int       a         = left + (right - left) / 2; // 中心のx座標
			const int b         = top + (bottom - top) / 2;  // 中心のy座標
			const int r         = right - a;                 // 半径
			const int distance  = 300;                       // 移動する距離
			const int wait_msec = 10;                        // 待機する秒数（ミリ秒）

			// 円は1ドットづつ移動する、つまり中心が1ドットづつ移動していく
			for (int i = 0; i <= distance; i++, a++) {
				for (x = a - r; x <= a + r; x++) {
					for (y = b - r; y <= b + r; y++) {
						if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
							SetPixel(hdc, x, y, RGB(0, 0, 0));
						}
					}
				}
				Sleep(wait_msec);
				// 描画した円を白で塗りつぶす
				// ただし、移動し終わった時は円を残す
				if (i != distance) {
					for (x = a - r; x <= a + r; x++) {
						for (y = b - r; y <= b + r; y++) {
							if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
								SetPixel(hdc, x, y, RGB(255, 255, 255));
							}
						}
					}
				}
			}
		}

		// ２点を結ぶ線分
		{
			const int x1 = 180;
			const int y1 = 60;
			const int x2 = 230;
			const int y2 = 20;
			
			for (y = MIN(y1, y2); y < MAX(y1, y2); y++) {
				for (x = MIN(x1, x2); x < MAX(x1, x2); x++) {
					if (fabs((double)((x - x1) * (y2- y1) - (x2 - x1) * (y - y1))) < 30) {
						SetPixel(hdc, x, y, RGB(0, 0, 0));
					}
				}
			}
		}

		// イニシャル
		{
			// 線分のデータ
			const int src[][2][2] = {
				{{400, 400}, {425, 450}},
				{{450, 400}, {425, 450}},
				{{500, 450}, {550, 500}}
			};
			// 描画する線分の数
			const size_t src_num = sizeof(src) / sizeof(src[0]);

			for (int i = 0; i < src_num; i++) {
				const int x1 = src[i][0][0];
				const int y1 = src[i][0][1];
				const int x2 = src[i][1][0];
				const int y2 = src[i][1][1];
			
				/**
				 * 線分を描画する
				 * ただし、x1とx2が等しい、y1とy2が等しい場合（線分がx座標軸またはy座標軸と並行する）も考慮している
				 */
				for (y = MIN(y1, y2); y < MAX(y1, y2) || (y == y1 && y == y2); y++) {
					for (x = MIN(x1, x2); x < MAX(x1, x2) || (x == x1 && x == x2); x++) {
						if (abs((x - x1) * (y2- y1) - (x2 - x1) * (y - y1)) < 50) {
							SetPixel(hdc, x, y, RGB(0, 0, 0));
						}
					}
				}
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
