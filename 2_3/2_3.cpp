// 2_3.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "2_3.h"
#include <stdio.h>
#include <math.h>

#define MAX_LOADSTRING 100

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x > y ? y : x)

// �O���[�o���ϐ�:
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��

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
	MSG msg;
	HACCEL hAccelTable;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_3));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2_3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_3);
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

		// �~��`�����
		{
			const int a = 100; // ���S��x���W
			const int b = 100; // ���S��y���W
			const int r = 50;  // ���a

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					// �~�̕������Ɋ�Â��ĉ~��`��
					if (pow(x - a, 2.0) + pow(y - b, 2.0) == pow(r, 2.0)) {
						SetPixel(hdc, x, y, RGB(0, 0, 0));
					}
				}
			}
		}

		/**
		 * �ۑ�1
		 * (110, 10)����(210, 110)�͈̔͂ɁA�ڂ��āA�������Ԃ��h��Ԃ��ꂽ�~��`���B 
		 */
		{
			const int left   = 110;                       // �`��͈͂̍����x���W
			const int top    = 10;                        // �`��͈͂̍����y���W
			const int right  = 210;                       // �`��͈͂̉E����x���W
			const int bottom = 110;                       // �`��͈͂̉E����y���W
			const int a      = left + (right - left) / 2; // ���S��x���W
			const int b      = top + (bottom - top) / 2;  // ���S��y���W
			const int r      = right - a;                 // ���a

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					// ����h��Ԃ��̂�==�ŕӂ�����`�悷��̂ł͂Ȃ��A�~�̒����`�悷��
					if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
						SetPixel(hdc, x, y, RGB(255, 0, 0));
					}
				}
			}
		}

		/**
		 * �ۑ�2
		 * (110, 210)����(210, 310)�͈̔͂ɐڂ���h�[�i�c��̉~��`��
		 */
		{
			const int left   = 110;                       // �`��͈͂̍����x���W
			const int top    = 210;                       // �`��͈͂̍����y���W
			const int right  = 210;                       // �`��͈͂̉E����x���W
			const int bottom = 310;                       // �`��͈͂̉E����y���W
			const int a      = left + (right - left) / 2; // ���S��x���W
			const int b      = top + (bottom - top) / 2;  // ���S��y���W
			const int r      = right - a;                 // ���a
			const int void_r = 25;                        // �󓴂̔��a�i�C�Ӂj

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					const double xa2 = pow(x - a, 2.0); // (x - a)^2
					const double yb2 = pow(y - b, 2.0); // (y - b)^2
					// �󓴂̉~�̒��͕`�ʂ��Ȃ��悤�ɂ���
					if (xa2 + yb2 < pow(r, 2.0) && xa2 + yb2 >= pow(void_r, 2.0)) {
						SetPixel(hdc, x, y, RGB(0, 0, 0));
					}
				}
			}
		}

		/**
		 * �ۑ�3
		 * (110, 310)����(210, 410)�Ɉȉ��̉~��`��
		 * �ԁ@��
		 * �@��
		 */
		{
			const int left      = 110;                       // �`��͈͂̍����x���W
			const int top       = 310;                        // �`��͈͂̍����y���W
			const int right     = 210;                       // �`��͈͂̉E����x���W
			const int bottom    = 410;                       // �`��͈͂̉E����y���W
			const int a         = left + (right - left) / 2; // ���S��x���W
			const int b         = top + (bottom - top) / 2;  // ���S��y���W
			const int r         = right - a;                 // ���a
			const COLORREF red  = RGB(255, 0, 0);            // ��
			const COLORREF blue = RGB(0, 0, 255);            // ��

			for (x = a - r; x <= a + r; x++) {
				for (y = b - r; y <= b + r; y++) {
					if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
						COLORREF col;
						// ���S���獶��܂��́A�E���̏ꍇ�͐�
						if ((x < a && y < b) || (x >= a && y >= b)) {
							col = red;
						} else { // �����łȂ��ꍇ�͐�
							col = blue;
						}
						SetPixel(hdc, x, y, col);
					}
				}
			}
		}

		/**
		 * �ۑ�4�i�`�������W���j
		 * (0, 0) ~ (100, 100)�̉~��(300, 0) ~ (400, 100)�̉~�Ɉړ�
		 */
		{
			const int left      = 0;                         // �`��͈͂̍����x���W
			const int top       = 0;                         // �`��͈͂̍����y���W
			const int right     = 100;                       // �`��͈͂̉E����x���W
			const int bottom    = 100;                       // �`��͈͂̉E����y���W
			int       a         = left + (right - left) / 2; // ���S��x���W
			const int b         = top + (bottom - top) / 2;  // ���S��y���W
			const int r         = right - a;                 // ���a
			const int distance  = 300;                       // �ړ����鋗��
			const int wait_msec = 10;                        // �ҋ@����b���i�~���b�j

			// �~��1�h�b�g�Âړ�����A�܂蒆�S��1�h�b�g�Âړ����Ă���
			for (int i = 0; i <= distance; i++, a++) {
				for (x = a - r; x <= a + r; x++) {
					for (y = b - r; y <= b + r; y++) {
						if (pow(x - a, 2.0) + pow(y - b, 2.0) < pow(r, 2.0)) {
							SetPixel(hdc, x, y, RGB(0, 0, 0));
						}
					}
				}
				Sleep(wait_msec);
				// �`�悵���~�𔒂œh��Ԃ�
				// �������A�ړ����I��������͉~���c��
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

		// �Q�_�����Ԑ���
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

		// �C�j�V����
		{
			// �����̃f�[�^
			const int src[][2][2] = {
				{{400, 400}, {425, 450}},
				{{450, 400}, {425, 450}},
				{{500, 450}, {550, 500}}
			};
			// �`�悷������̐�
			const size_t src_num = sizeof(src) / sizeof(src[0]);

			for (int i = 0; i < src_num; i++) {
				const int x1 = src[i][0][0];
				const int y1 = src[i][0][1];
				const int x2 = src[i][1][0];
				const int y2 = src[i][1][1];
			
				/**
				 * ������`�悷��
				 * �������Ax1��x2���������Ay1��y2���������ꍇ�i������x���W���܂���y���W���ƕ��s����j���l�����Ă���
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
