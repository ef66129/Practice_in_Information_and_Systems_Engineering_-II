// 2_5.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "2_5.h"
#include <stdio.h>
#include <limits.h>

#define SRC_IMG_1 "PA276186.raw"                 // 1���ڂ̉摜�̃t�@�C����
#define SRC_IMG_2 "22301877979_c7a62eb6f9_o.raw" // 2���ڂ̉摜�̃t�@�C����
#define IMG_WIDTH 1024                           // �摜�̕�
#define IMG_HEIGHT 768                           // �摜�̍���
#define KADAI2_VAL 2                             // �ۑ�2�̔{��
#define KADAI4_N_IVAL 0.1                        // �ۑ�4�̕ϐ�n�̊Ԋu
#define KADAI4_N_MAX 1.0                         // �ۑ�4�̕ϐ�n�̍ő�l
#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;						 // ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];			 // �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];	 // ���C�� �E�B���h�E �N���X��
unsigned char r[IMG_HEIGHT][IMG_WIDTH];  // 1���ڂ̉摜��r
unsigned char g[IMG_HEIGHT][IMG_WIDTH];  // 1���ڂ̉摜��g
unsigned char b[IMG_HEIGHT][IMG_WIDTH];  // 1���ڂ̉摜��b
unsigned char r2[IMG_HEIGHT][IMG_WIDTH]; // 2���ڂ̉摜��r
unsigned char g2[IMG_HEIGHT][IMG_WIDTH]; // 2���ڂ̉摜��g
unsigned char b2[IMG_HEIGHT][IMG_WIDTH]; // 2���ڂ̉摜��b

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
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

 	// TODO: �����ɃR�[�h��}�����Ă��������B
	FILE *fp;
	int x, y;

	// �t�@�C�����J��
	if ((fp = fopen(SRC_IMG_1, "rb"))) {
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGB�����ꂼ�����ǂݍ���
				fread(&r[y][x], sizeof(r[y][x]), 1, fp);
				fread(&g[y][x], sizeof(g[y][x]), 1, fp);
				fread(&b[y][x], sizeof(b[y][x]), 1, fp);
			}
		}
		// �t�@�C�������
		fclose(fp);
	}
	if ((fp = fopen(SRC_IMG_2, "rb"))) {
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGB�����ꂼ�����ǂݍ���
				fread(&r2[y][x], sizeof(r2[y][x]), 1, fp);
				fread(&g2[y][x], sizeof(g2[y][x]), 1, fp);
				fread(&b2[y][x], sizeof(b2[y][x]), 1, fp);
			}
		}
		// �t�@�C�������
		fclose(fp);
	}

	MSG msg;
	HACCEL hAccelTable;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_5));

	// ���C�� ���b�Z�[�W ���[�v:
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
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
//  �R�����g:
//
//    ���̊֐�����юg�����́A'RegisterClassEx' �֐����ǉ����ꂽ
//    Windows 95 ���O�� Win32 �V�X�e���ƌ݊�������ꍇ�ɂ̂ݕK�v�ł��B
//    �A�v���P�[�V�������A�֘A�t����ꂽ
//    �������`���̏������A�C�R�����擾�ł���悤�ɂ���ɂ́A
//    ���̊֐����Ăяo���Ă��������B
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
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

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
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
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
		// �I�����ꂽ���j���[�̉��:
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
		// TODO: �`��R�[�h�������ɒǉ����Ă�������...
				int x, y;

		// �摜�̕\��
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				SetPixel(hdc, x, y, RGB(r[y][x], g[y][x], b[y][x]));
			}
		}

#if 0
		// �ۑ�1
		// ���E�𔽓]���ĕ\��
		/*
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				SetPixel(hdc, IMG_WIDTH - x, y, RGB(r[y][x], g[y][x], b[y][x]));
			}
		}
		*/

		// �ۑ�2
		// �摜�𖾂邭����
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

		// �{���������I�Ɍ�����
		{
			int max = 0; // �ő�l
			double m;    // �{��

			// RGB�̍ő�l�����߂�
			for (y = 0; y < IMG_HEIGHT; y++) {
				for (x = 0; x < IMG_WIDTH; x++) {
					if (max < r[y][x]) max = r[y][x];
					if (max < g[y][x]) max = g[y][x];
					if (max < b[y][x]) max = b[y][x];
				}
			}
			// �{�������߂�
			m = (double)UCHAR_MAX / max;

			// �{������RGB�����ꂼ��l�𑝂₵�ĕ\��
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
		// �ۑ�3
		// �u�����h
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGB���ꂼ��̕��ς�\��
				SetPixel(hdc, x, y, RGB(
					(r[y][x] + r2[y][x]) / 2,
					(g[y][x] + g2[y][x]) / 2,
					(b[y][x] + b2[y][x]) / 2));
			}
		}

		// �ۑ�4
		// ���[�t�B���O�̊�b
		{
			double n; // �u�����h���銄��

			// 1���ڂ̉摜���u�����h���銄���𑝂₵�Ȃ���摜��\��
			// (1���ڂ̊�����n�Ȃ�2���ڂ�(1-n))
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

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
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
