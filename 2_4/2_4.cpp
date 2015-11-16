// 2_4.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "2_4.h"
#include <stdio.h>

#define SRC_IMG "Penguins.raw"              // 画像のファイル名
#define DEST_IMG "Penguins_resized.raw"     // 書き込む画像のファイル名
#define IMG_WIDTH 1024                      // 画像の幅
#define IMG_HEIGHT 768                      // 画像の高さ
#define RESIZED_IMG_WIDTH (IMG_WIDTH / 2)   // リサイズ後の画像の幅
#define RESIZED_IMG_HEIGHT (IMG_HEIGHT / 2) // リサイズ後の画像の高さ
#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                         // 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];                           // タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];                     // メイン ウィンドウ クラス名
unsigned char r[IMG_HEIGHT][IMG_WIDTH];                  // 画像のr
unsigned char g[IMG_HEIGHT][IMG_WIDTH];                  // 画像のg
unsigned char b[IMG_HEIGHT][IMG_WIDTH];                  // 画像のb
unsigned char r2[RESIZED_IMG_HEIGHT][RESIZED_IMG_WIDTH]; // リサイズ後の画像のr
unsigned char g2[RESIZED_IMG_HEIGHT][RESIZED_IMG_WIDTH]; // リサイズ後の画像のg
unsigned char b2[RESIZED_IMG_HEIGHT][RESIZED_IMG_WIDTH]; // リサイズ後の画像のg

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
	if ((fp = fopen(SRC_IMG, "rb"))) {
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

	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_4));

	// メイン メッセージ ループ:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// ファイルの保存(書き込み)
	if ((fp = fopen(DEST_IMG, "wb"))) {
		for (y = 0; y < RESIZED_IMG_HEIGHT; y++) {
			for (x = 0; x < RESIZED_IMG_WIDTH; x++) {
				// RGBをそれぞれ一つずつ書き込み
				fwrite(&r2[y][x], sizeof(r2[y][x]), 1, fp);
				fwrite(&g2[y][x], sizeof(g2[y][x]), 1, fp);
				fwrite(&b2[y][x], sizeof(b2[y][x]), 1, fp);
			}
		}
		// ファイルを閉じる
		fclose(fp);
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2_4));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_4);
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

		// 画像の縮小
		int x2, y2;

		// <画像の幅、高さ>/<縮小後の画像の幅、高さ>だけ飛ばして配列に入れる
		for (y = y2 = 0; y < IMG_HEIGHT; y += IMG_HEIGHT / RESIZED_IMG_HEIGHT, y2++) {
			for (x = x2 = 0; x < IMG_WIDTH; x += IMG_WIDTH / RESIZED_IMG_WIDTH, x2++) {
				r2[y2][x2] = r[y][x];
				g2[y2][x2] = g[y][x];
				b2[y2][x2] = b[y][x];
			}
		}
		// 画像の表示
		for (y = 0; y < RESIZED_IMG_HEIGHT; y++) {
			for (x = 0; x < RESIZED_IMG_WIDTH; x++) {
				SetPixel(hdc, x, y, RGB(r2[y][x], g2[y][x], b2[y][x]));
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
