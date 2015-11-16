// 2_5.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "2_5.h"
#include <stdio.h>
#include <limits.h>

#define SRC_IMG_1 "PA276186.raw"                 // 1枚目の画像のファイル名
#define SRC_IMG_2 "22301877979_c7a62eb6f9_o.raw" // 2枚目の画像のファイル名
#define IMG_WIDTH 1024                           // 画像の幅
#define IMG_HEIGHT 768                           // 画像の高さ
#define KADAI2_VAL 2                             // 課題2の倍率
#define KADAI4_N_IVAL 0.1                        // 課題4の変数nの間隔
#define KADAI4_N_MAX 1.0                         // 課題4の変数nの最大値
#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;						 // 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];			 // タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];	 // メイン ウィンドウ クラス名
unsigned char r[IMG_HEIGHT][IMG_WIDTH];  // 1枚目の画像のr
unsigned char g[IMG_HEIGHT][IMG_WIDTH];  // 1枚目の画像のg
unsigned char b[IMG_HEIGHT][IMG_WIDTH];  // 1枚目の画像のb
unsigned char r2[IMG_HEIGHT][IMG_WIDTH]; // 2枚目の画像のr
unsigned char g2[IMG_HEIGHT][IMG_WIDTH]; // 2枚目の画像のg
unsigned char b2[IMG_HEIGHT][IMG_WIDTH]; // 2枚目の画像のb

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
	FILE *fp;
	int x, y;

	// ファイルを開く
	if ((fp = fopen(SRC_IMG_1, "rb"))) {
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGBをそれぞれ一つずつ読み込み
				fread(&r[y][x], sizeof(r[y][x]), 1, fp);
				fread(&g[y][x], sizeof(g[y][x]), 1, fp);
				fread(&b[y][x], sizeof(b[y][x]), 1, fp);
			}
		}
		// ファイルを閉じる
		fclose(fp);
	}
	if ((fp = fopen(SRC_IMG_2, "rb"))) {
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGBをそれぞれ一つずつ読み込み
				fread(&r2[y][x], sizeof(r2[y][x]), 1, fp);
				fread(&g2[y][x], sizeof(g2[y][x]), 1, fp);
				fread(&b2[y][x], sizeof(b2[y][x]), 1, fp);
			}
		}
		// ファイルを閉じる
		fclose(fp);
	}

	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_5));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2_5));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_5);
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

		// 画像の表示
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				SetPixel(hdc, x, y, RGB(r[y][x], g[y][x], b[y][x]));
			}
		}

#if 0
		// 課題1
		// 左右を反転して表示
		/*
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				SetPixel(hdc, IMG_WIDTH - x, y, RGB(r[y][x], g[y][x], b[y][x]));
			}
		}
		*/

		// 課題2
		// 画像を明るくする
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				if (r[y][x] * KADAI2_VAL > UCHAR_MAX
					|| g[y][x] * KADAI2_VAL > UCHAR_MAX
					|| b[y][x] * KADAI2_VAL > UCHAR_MAX) {
					SetPixel(hdc, x, y, RGB(255, 255, 255));
				} else {
					SetPixel(hdc, x, y, RGB(r[y][x], g[y][x], b[y][x]));
				}
			}
		}

		// 倍率を自動的に見つける
		{
			int max = 0; // 最大値
			double m;    // 倍率

			// RGBの最大値を求める
			for (y = 0; y < IMG_HEIGHT; y++) {
				for (x = 0; x < IMG_WIDTH; x++) {
					if (max < r[y][x]) max = r[y][x];
					if (max < g[y][x]) max = g[y][x];
					if (max < b[y][x]) max = b[y][x];
				}
			}
			// 倍率を求める
			m = (double)UCHAR_MAX / max;

			// 倍率だけRGBをそれぞれ値を増やして表示
			for (y = 0; y < IMG_HEIGHT; y++) {
				for (x = 0; x < IMG_WIDTH; x++) {
					SetPixel(hdc, x, y, RGB(
						(unsigned char)(r[y][x] * m),
						(unsigned char)(g[y][x] * m),
						(unsigned char)(b[y][x] * m)));
				}
			}
		}
#endif
		// 課題3
		// ブレンド
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGBそれぞれの平均を表示
				SetPixel(hdc, x, y, RGB(
					(r[y][x] + r2[y][x]) / 2,
					(g[y][x] + g2[y][x]) / 2,
					(b[y][x] + b2[y][x]) / 2));
			}
		}

		// 課題4
		// モーフィングの基礎
		{
			double n; // ブレンドする割合

			// 1枚目の画像をブレンドする割合を増やしながら画像を表示
			// (1枚目の割合がnなら2枚目は(1-n))
			for (n = 0.0; n <= KADAI4_N_MAX; n += KADAI4_N_IVAL) {
				for (y = 0; y < IMG_HEIGHT; y++) {
					for (x = 0; x < IMG_WIDTH; x++) {
						SetPixel(hdc, x, y, RGB(
							r[y][x] * n + r2[y][x] * (KADAI4_N_MAX - n),
							g[y][x] * n + g2[y][x] * (KADAI4_N_MAX - n),
							b[y][x] * n + b2[y][x] * (KADAI4_N_MAX - n)));
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
