// 2_6.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "2_6.h"
#include <stdio.h>

#define MAX_LOADSTRING    100
#define D_NUM             100000                // 配列dの要素数
#define WAV_DATASIZE_POS  40                    // wavファイルのデータのバイト数が格納されている場所
#define WAV_DATASIZE_SIZE 4                     // wavファイルのデータのバイト数のバイト数
#define WAV_FILESIZE_POS  4                     // wavファイルのファイルのバイト数が格納されている場所
#define WAV_FILESIZE_SIZE 4                     // wavファイルのファイルのバイト数のバイト数
#define WAV_HEADERSIZE    44                    // wavファイルのヘッダの大きさ

// グローバル変数:
HINSTANCE hInst;				// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];			// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];		// メイン ウィンドウ クラス名
unsigned char d[D_NUM];                         // 音声データを格納する配列

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

		/*
			課題2
		*/
		{
			FILE          *fp_do;
			FILE          *fp_re;
			FILE          *fp_mi;
			FILE          *fp_doremi;
			unsigned char header[WAV_HEADERSIZE];
			size_t        datasize_do;
			size_t        datasize_re;
			size_t        datasize_mi;
			size_t        datasize_doremi;
			size_t        filesize_doremi;

			// ファイルのオープン
			if ((fp_do = fopen("DO.wav", "rb"))
				&& (fp_re = fopen("RE.wav", "rb"))
				&& (fp_mi = fopen("MI.wav", "rb"))
				&& (fp_doremi = fopen("output.wav", "wb"))) {
					// ヘッダ部の読み込み
					// ヘッダ部はバイト数の部分だけしか変わらないので1つ読み込む
					fread(header, sizeof(header[0]), WAV_HEADERSIZE, fp_do);
					
					// 各読み込みファイルのヘッダのデータのバイト数を読み込む
					fseek(fp_do, WAV_DATASIZE_POS, SEEK_SET);
					fread(&datasize_do, WAV_DATASIZE_SIZE, 1, fp_do);

					fseek(fp_re, WAV_DATASIZE_POS, SEEK_SET);
					fread(&datasize_re, WAV_DATASIZE_SIZE, 1, fp_re);

					fseek(fp_mi, WAV_DATASIZE_POS, SEEK_SET);
					fread(&datasize_mi, WAV_DATASIZE_SIZE, 1, fp_mi);

					// 書き込むファイルのデータ数は各ファイルのバイト数の合計
					datasize_doremi = datasize_do + datasize_re + datasize_mi;
					// ファイル全体はデータ部のバイト数 + ヘッダ部のバイト数(44)
					filesize_doremi = datasize_doremi + WAV_HEADERSIZE;

					// ヘッダを書き換える
					memcpy(&header[WAV_FILESIZE_POS], &filesize_doremi, WAV_FILESIZE_SIZE);
					memcpy(&header[WAV_DATASIZE_POS], &datasize_doremi, WAV_DATASIZE_SIZE);

					// 各読み込みファイルの読み出し位置をデータ部の先頭にセット
					fseek(fp_do, WAV_HEADERSIZE, SEEK_SET);
					fseek(fp_re, WAV_HEADERSIZE, SEEK_SET);
					fseek(fp_mi, WAV_HEADERSIZE, SEEK_SET);

					// ヘッダ部の書き込み
					fwrite(header, sizeof(header[0]), WAV_HEADERSIZE, fp_doremi);

					// 各読み込みファイルからデータ部のデータを読み出して順に書き出すファイルのデータ部に書き込む
					fread(d, sizeof(d[0]), datasize_do, fp_do);
					fwrite(d, sizeof(d[0]), datasize_do, fp_doremi);

					fread(d, sizeof(d[0]), datasize_re, fp_re);
					fwrite(d, sizeof(d[0]), datasize_re, fp_doremi);

					fread(d, sizeof(d[0]), datasize_mi, fp_mi);
					fwrite(d, sizeof(d[0]), datasize_mi, fp_doremi);
			}

			// ファイルのクローズ
			if (fp_do)     fclose(fp_do);
			if (fp_re)     fclose(fp_re);
			if (fp_mi)     fclose(fp_mi);
			if (fp_doremi) fclose(fp_doremi);

		}

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_6));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2_6));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_6);
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

		/*
			課題1
		*/
		{
			FILE *fp;
			int  ddo;

			// 音声ファイルの読み込み
			if ((fp = fopen("DO.wav", "rb"))) {
				// データのバイト数が格納されている場所に移動
				// fseek(fp, 40, SEEK_SET);
				fseek(fp,             // ファイルポインタ
					WAV_DATASIZE_POS, // 位置
					SEEK_SET);        // 基準
				// データのバイト数を読み込み
				// fread(&ddo, 4, 1, fp);
				fread(&ddo, WAV_DATASIZE_SIZE, 1, fp);

				// データを読み込み
				// 読み込み位置はすでにデータの先頭になっている
				// int i;
				//
				// for (i = 0; i < ddo; i++) {
				//	fread(&d[i], 1, 1, fp);
				// }
				fread(d, sizeof(d[0]), (size_t)ddo, fp);

				fclose(fp);

				// 音声データを描画する
				for (int i = 0; i < ddo; ++i) {
					// 音声データには音の高さが記録されているので、y座標を音声データの値にする
					SetPixel(hdc, i, d[i], RGB(0, 0, 0));
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
