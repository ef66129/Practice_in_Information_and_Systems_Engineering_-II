// 2_6.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "2_6.h"
#include <stdio.h>

#define MAX_LOADSTRING    100
#define D_NUM             100000                // �z��d�̗v�f��
#define WAV_DATASIZE_POS  40                    // wav�t�@�C���̃f�[�^�̃o�C�g�����i�[����Ă���ꏊ
#define WAV_DATASIZE_SIZE 4                     // wav�t�@�C���̃f�[�^�̃o�C�g���̃o�C�g��
#define WAV_FILESIZE_POS  4                     // wav�t�@�C���̃t�@�C���̃o�C�g�����i�[����Ă���ꏊ
#define WAV_FILESIZE_SIZE 4                     // wav�t�@�C���̃t�@�C���̃o�C�g���̃o�C�g��
#define WAV_HEADERSIZE    44                    // wav�t�@�C���̃w�b�_�̑傫��

// �O���[�o���ϐ�:
HINSTANCE hInst;				// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];			// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];		// ���C�� �E�B���h�E �N���X��
unsigned char d[D_NUM];                         // �����f�[�^���i�[����z��

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

		/*
			�ۑ�2
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

			// �t�@�C���̃I�[�v��
			if ((fp_do = fopen("DO.wav", "rb"))
				&& (fp_re = fopen("RE.wav", "rb"))
				&& (fp_mi = fopen("MI.wav", "rb"))
				&& (fp_doremi = fopen("output.wav", "wb"))) {
					// �w�b�_���̓ǂݍ���
					// �w�b�_���̓o�C�g���̕������������ς��Ȃ��̂�1�ǂݍ���
					fread(header, sizeof(header[0]), WAV_HEADERSIZE, fp_do);
					
					// �e�ǂݍ��݃t�@�C���̃w�b�_�̃f�[�^�̃o�C�g����ǂݍ���
					fseek(fp_do, WAV_DATASIZE_POS, SEEK_SET);
					fread(&datasize_do, WAV_DATASIZE_SIZE, 1, fp_do);

					fseek(fp_re, WAV_DATASIZE_POS, SEEK_SET);
					fread(&datasize_re, WAV_DATASIZE_SIZE, 1, fp_re);

					fseek(fp_mi, WAV_DATASIZE_POS, SEEK_SET);
					fread(&datasize_mi, WAV_DATASIZE_SIZE, 1, fp_mi);

					// �������ރt�@�C���̃f�[�^���͊e�t�@�C���̃o�C�g���̍��v
					datasize_doremi = datasize_do + datasize_re + datasize_mi;
					// �t�@�C���S�̂̓f�[�^���̃o�C�g�� + �w�b�_���̃o�C�g��(44)
					filesize_doremi = datasize_doremi + WAV_HEADERSIZE;

					// �w�b�_������������
					memcpy(&header[WAV_FILESIZE_POS], &filesize_doremi, WAV_FILESIZE_SIZE);
					memcpy(&header[WAV_DATASIZE_POS], &datasize_doremi, WAV_DATASIZE_SIZE);

					// �e�ǂݍ��݃t�@�C���̓ǂݏo���ʒu���f�[�^���̐擪�ɃZ�b�g
					fseek(fp_do, WAV_HEADERSIZE, SEEK_SET);
					fseek(fp_re, WAV_HEADERSIZE, SEEK_SET);
					fseek(fp_mi, WAV_HEADERSIZE, SEEK_SET);

					// �w�b�_���̏�������
					fwrite(header, sizeof(header[0]), WAV_HEADERSIZE, fp_doremi);

					// �e�ǂݍ��݃t�@�C������f�[�^���̃f�[�^��ǂݏo���ď��ɏ����o���t�@�C���̃f�[�^���ɏ�������
					fread(d, sizeof(d[0]), datasize_do, fp_do);
					fwrite(d, sizeof(d[0]), datasize_do, fp_doremi);

					fread(d, sizeof(d[0]), datasize_re, fp_re);
					fwrite(d, sizeof(d[0]), datasize_re, fp_doremi);

					fread(d, sizeof(d[0]), datasize_mi, fp_mi);
					fwrite(d, sizeof(d[0]), datasize_mi, fp_doremi);
			}

			// �t�@�C���̃N���[�Y
			if (fp_do)     fclose(fp_do);
			if (fp_re)     fclose(fp_re);
			if (fp_mi)     fclose(fp_mi);
			if (fp_doremi) fclose(fp_doremi);

		}

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2_6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2_6));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2_6));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2_6);
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

		/*
			�ۑ�1
		*/
		{
			FILE *fp;
			int  ddo;

			// �����t�@�C���̓ǂݍ���
			if ((fp = fopen("DO.wav", "rb"))) {
				// �f�[�^�̃o�C�g�����i�[����Ă���ꏊ�Ɉړ�
				// fseek(fp, 40, SEEK_SET);
				fseek(fp,             // �t�@�C���|�C���^
					WAV_DATASIZE_POS, // �ʒu
					SEEK_SET);        // �
				// �f�[�^�̃o�C�g����ǂݍ���
				// fread(&ddo, 4, 1, fp);
				fread(&ddo, WAV_DATASIZE_SIZE, 1, fp);

				// �f�[�^��ǂݍ���
				// �ǂݍ��݈ʒu�͂��łɃf�[�^�̐擪�ɂȂ��Ă���
				// int i;
				//
				// for (i = 0; i < ddo; i++) {
				//	fread(&d[i], 1, 1, fp);
				// }
				fread(d, sizeof(d[0]), (size_t)ddo, fp);

				fclose(fp);

				// �����f�[�^��`�悷��
				for (int i = 0; i < ddo; ++i) {
					// �����f�[�^�ɂ͉��̍������L�^����Ă���̂ŁAy���W�������f�[�^�̒l�ɂ���
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
