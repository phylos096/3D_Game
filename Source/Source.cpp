/*#include <windows.h>
#include<tchar.h>

LRESULT WINAPI MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:

		//WM_QUIT�𒊏o
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPInst,
	LPSTR lpCmd,
	int nCmd)
{
	//�E�B���h�E�N���X�̓o�^
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,hInst,NULL,NULL,NULL,NULL,_T("My Window"),NULL };

	//�E�B���h�E�쐬
	HWND hwnd = CreateWindow(_T("BUTTON"), _T("3D_Game_PG"), WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInst, NULL);

	ShowWindow(hwnd, SW_SHOWDEFAULT);

	//���b�Z�[�W���[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	//�I������
	UnregisterClass(_T("My Window"), hInst);

	return 0;
}*/

