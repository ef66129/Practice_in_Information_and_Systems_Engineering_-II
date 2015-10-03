// 1410990063_PISE2.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "2_2.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

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
	LoadString(hInstance, IDC_MY2_2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_2));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY2_2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_2);
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

		int x;
		for (x = 10; x <= 100; ++x)
			SetPixel(hdc, x, 20, RGB(0, 0, 0));
		int y;
		for (y = 0; y <= 100; ++y)
			SetPixel(hdc, 55, y, RGB(0, 0, 0));

		/*
		 * �ۑ�1
		 * for����p����(0, 0)����(200, 200)�܂ł̎ΐ���`���v���O���������
		 */
		{
			int i;
			for (i = 0; i <= 200; ++i) {
				SetPixel(hdc, i, i, RGB(0, 0, 0));
			}
		}

		/*
		 * �ۑ�2
		 * �����`��`���v���O���������
		 */
		{
			const int start_x = 10;  // �����x���W
			const int start_y = 10; // �����y���W
			const int end_x   = 110; // �E����x���W
			const int end_y   = 110; // �E����y���W
			const int ival  = 255 / (end_y - start_y); //�F�̊Ԋu

			for (x = start_x; x <= end_x; ++x) {
				for (y = start_y; y <= end_y; ++y) {
					SetPixel(hdc, x, y, RGB(0, 0, 0));
				}
			}
		}

		/* 
		 * �ۑ�3
		 * ����(10, 110), �E��(110, 210)�̐����`�Ō��Ԃ�1�s�N�Z���̏c�̃X�g���C�v
		 */
		{
			const int start_x = 10;  // �����x���W
			const int start_y = 110; // �����y���W
			const int end_x   = 110; // �E����x���W
			const int end_y   = 210; // �E����y���W
			const int ival    = 1;   // �Ԋu
			
			for (x = start_x; x <= end_x; x += 1 + ival) {
				for (y = start_y; y <= end_y; ++y) {
					SetPixel(hdc, x, y, RGB(0, 0, 0));
				}
			}
		}

		/*
		 * �ۑ�4
		 * (10, 210)�`(110, 310)�̐����`�Ō��Ԃ�2��f�̓_�������`
		 */
		{
			const int start_x = 10;  // �����x���W
			const int start_y = 210; // �����y���W
			const int end_x   = 110; // �E����x���W
			const int end_y   = 310; // �E����y���W
			const int ival    = 2;   // �Ԋu

			for (x = start_x; x <= end_x; x += 1 + ival) {
				for (y = start_y; y <= end_y; y += 1 + ival) {
					SetPixel(hdc, x, y, RGB(0, 0, 0));
				}
			}
		}

		/*
		 * ���ʉۑ�
		 * �ۑ�2�̐����`�̉E���ɓ����T�C�Y�̐����`
		 * �������A�F����->�ɃO���f�[�V����
		 */
		{
			const int start_x = 110; // �����x���W
			const int start_y = 10;  // �����y���W
			const int end_x   = 210; // �E����x���W
			const int end_y   = 110; // �E����y���W
			const int ival    = 255 / (end_y - start_y); //�F�̊Ԋu

			for (x = start_x; x <= end_x; ++x) {
				int i = 0;
				for (y = start_y; y <= end_y; ++y, ++i) {
					SetPixel(hdc, x, y,
						RGB(255 - i * ival,	0, 0 + i * ival));
				}
			}
		}

		/*
		 * �ۑ�5
		 * (10, 310)�`(110, 410)�̐����`
		 * �ԁ@��
		 * ��  ��
		 */
		{
			const int start_x = 10;                              // �����x���W
			const int start_y = 310;                             // �����y���W
			const int end_x   = 110;                             // �E����x���W
			const int end_y   = 410;                             // �E����y���W
			const int mid_x   = start_x + (end_x - start_x) / 2; // ���S��x���W
			const int mid_y   = start_y + (end_y - start_y) / 2; // ���S��y���W
			COLORREF color;                                      // �F�̕ϐ�
			
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
		 * �ۑ�6
		 * �ۑ�5�̐����`�̉E���ɐ����`
		 * �� ��
		 * �� ��
		 */
		{
			const int start_x = 110;                             // �����x���W
			const int start_y = 310;                             // �����y���W
			const int end_x   = 210;                             // �E����x���W
			const int end_y   = 410;                             // �E����y���W
			const int mid_x   = start_x + (end_x - start_x) / 2; // �^�񒆂�x���W
			const int mid_y   = start_y + (end_y - start_y) / 2; // �^�񒆂�y���W
			const int sleep_msec = 100;                          // Sleep����b��(�~���b)
			const int count = 100;                               // �J��Ԃ���
			COLORREF color;                                      // �F�̕ϐ�
			
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
