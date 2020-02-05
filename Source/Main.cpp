#include "Direct3D.h"
#include "DirectXFont.h"
#include "Player.h"
#include "CreateBox.h"

/******************************************************

		Y
		↑
		|
		|		Z(奥)
		|      ↗
		|     /
		|    /
		|   /
		|  /
		| /
		|/______________________→ X

		空間のイメージ

********************************************************/

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


bool windowmode = true;	//ウィンドウモードの場合はマウス位置をAPIから取得する

// WinMain関数（アプリケーションの開始関数）
// コンソールアプリケーションと違い、コンソールを開かない
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const TCHAR* wcex_BASIC = _T("BASIC_WINDOW");
	// シンプルウィンドウクラス設定
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	//構造のサイズ
	wcex.cbSize = sizeof(WNDCLASSEX);
	//ウィンドウのスタイル
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	//ウィンドウのメッセージ処理関数のポインタ
	wcex.lpfnWndProc = WndProc;
	//ウィンドウクラス構造の後ろに割り当てる細くバイト数
	wcex.cbClsExtra = 0;
	//ウィンドウインスタンスの後ろに割り当てる細くバイト数
	wcex.cbWndExtra = 0;
	//ウィンドウプロシージャのインスタンスハンドル
	wcex.hInstance = hInstance;
	//アイコンハンドル
	wcex.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	//マウスカーソルハンドル
	wcex.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	//ウィンドウの背景食
	wcex.hbrBackground = NULL;
	//デフォルトメニュー名
	wcex.lpszMenuName = NULL;
	//ウィンドウクラス名
	wcex.lpszClassName = wcex_BASIC;
	//16×16の小さいサイズのアイコン
	wcex.hIconSm = NULL;

	//エラーチェック
	if (!RegisterClassEx(&wcex))return FALSE;

	// ウィンドウの作成
	HWND hWnd = CreateWindowEx(0,wcex_BASIC,
		_T("Application"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		WINDOW_WIDTH, 
		WINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)return FALSE;

	//Direct3Dの初期化
	Direct3D direct3D;
	direct3D.Create(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);

	//ZバッファON
	direct3D.pDevice3D->SetRenderState(D3DRS_ZENABLE, true);
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	// フォント作成
	DirectXFont font[3];
	font[0].Create(direct3D.pDevice3D, 64);
	font[1].Create(direct3D.pDevice3D, 32);
	font[2].Create(direct3D.pDevice3D, 16);

	Player player(hInstance,hWnd,direct3D.pDevice3D);

	LoadModel model;
	BaseObject modelObje;
	Camera camera;
	modelObje.Value_Scale_X(0.1f);
	modelObje.Value_Scale_Y(0.1f);
	modelObje.Value_Scale_Z(0.1f);
	modelObje.Value_PosY(-0.5f);
	modelObje.Value_PosZ(1.5f);
	modelObje.Update();
	model.Load(_T("Model/Can.x"), _T("Model/Can.x"),direct3D.pDevice3D,&modelObje.Value_Position());

	BOX3D box;
	box.CreateBOX(10, 0, 0, 10);

		// メッセージループ
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		// アプリケーションに送られてくるメッセージをメッセージキューから取得する
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);	// アプリケーションの各ウィンドウプロシージャにメッセージを転送する
		}
		// メッセージ処理をしていないとき
		else {

			// 描画開始
			if (SUCCEEDED(direct3D.pDevice3D->BeginScene()))
			{
				DWORD ClearColor = 0xff808080;	// 背景クリア色
				// 背景クリア
				direct3D.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, ClearColor, 1.0f, 0);

				box.Draw(direct3D.pDevice3D);
				D3DXVECTOR3 pPos = player.Value_Position();

				camera.Render(&model, &modelObje, direct3D.pDevice3D);


				font[2].Draw(0xff000000, 0, 50, _T("X:%lf  Y:%lf  Z:%lf"),player.baseobject->Value_PosX(),player.baseobject->Value_PosY(),player.baseobject->Value_PosZ());
				font[2].Draw(0xff000000, 0, 75, _T("Angle:%lf"),player.baseobject->Value_Angle());
				
				font[1].Draw(0xff000000, 0, 0, _T("やること:BOXの描写 \n"));
				
				player.Update();
				player.Draw(direct3D.pDevice3D);


				// 描画終了
				direct3D.pDevice3D->EndScene();
			}
			// 描画反映
			direct3D.pDevice3D->Present(NULL, NULL, NULL, NULL);
		}
	}
	return 0;
}

// ウィンドウプロシージャ、ウィンドウに対するメッセージ処理を行う
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg)
	{
	/*case WM_MOUSEMOVE:
		if (g_input) {
			if (windowmode) {
				g_input->Mouse()->SetCursorPos(LOWORD(lParam), HIWORD(lParam));
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);

	//キーが押された時呼ばれる
	//DirectInputに変えたいです
	/*case WM_KEYDOWN:
		switch ((CHAR)wParam) {
		case VK_LEFT:
		case 'A':
			MessageBox(hWnd, TEXT("キーが押されました"),
				TEXT("Kitty"), MB_ICONINFORMATION);
			break;
		case VK_RIGHT:
			break;
		
		}
		break;*/

	//キーボードのキーから指が離れた時呼ばれる
	case WM_KEYUP:
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		RECT rect;
		GetClientRect(hWnd, &rect);
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);

	}
	// デフォルトのメッセージ処理を行う
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*HRESULT InitD3D(HWND hWnd) {

	// Direct3D9オブジェクトの作成	
	//pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	//IDirect3D9コンポーネントの取得
	if (NULL == (pD3D9 = Direct3DCreate9(D3D_SDK_VERSION)))return FALSE;
	
	// ディスプレイ情報取得
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);

	D3DPRESENT_PARAMETERS D3DParam;
	ZeroMemory(&D3DParam, sizeof(D3DParam));
	//画面の大きさ
	D3DParam.BackBufferWidth = WINDOW_WIDTH;
	D3DParam.BackBufferHeight = WINDOW_HEIGHT;
	
	//画面のフォーマット情報
	D3DParam.BackBufferFormat = Display.Format;

	//バックバッファの数
	D3DParam.BackBufferCount = 1;

	//有効にすると「ジャギ消し効果」「アンチエイリアス」がかかる
	//対応していない場合があるので、Defaultにしておく。 
	D3DParam.MultiSampleType = D3DMULTISAMPLE_NONE;

	//マルチサンプルの品質レベル
	//MultiSampleTypeがNONEの場合、0で大丈夫
	D3DParam.MultiSampleQuality = 0;

	//フロントバッファとバックバッファの切り替え方法
	//今回のは、ディスプレイドライバが自動判断する
	D3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//描写ウィンドウハンドルの指定
	D3DParam.hDeviceWindow = hWnd;

	//スクリーンモードの指定
	//TRUE：フルスクリーン FALSE:ウィンドウ
	D3DParam.Windowed = TRUE;

	//深度ステンシルバッファの設定
	//TRUEなら3Dになる
	D3DParam.EnableAutoDepthStencil = TRUE;

	//ステンシルバッファのフォーマットを指定
	//EnableAutoDepthStencilがFALSEだと無視される
	//TRUEの場合D3DFORMAT列挙型で指定する必要がある
	D3DParam.AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;

	//バックバッファからフロントバッファへ転送する時の機能の設定
	//今はとりあえず0
	D3DParam.Flags = 0;

	//フルスクリーンのリフレッシュレートを指定
	//ウィンドウだと0にする必要がある
	D3DParam.FullScreen_RefreshRateInHz = 0;//;
	
	//スワップの書き換えタイミングを設定する
	//タイミングは垂直回帰線間隔を待つか待たないかがある。
	//待つ場合は、テアリングが出るのを防ぐ
	//待たない場合は、描写が最速になる
	D3DParam.PresentationInterval = D3DPRESENT_RATE_DEFAULT;// D3DPRESENT_INTERVAL_DEFAULT;

	// HALモードで3Dデバイス作成
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D))) {
		if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D))) {
			// REFモードで3Dデバイス作成
			if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
			{
				if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
				{
					// 3Dデバイス作成失敗
					pD3D9->Release();
					return -1;
				}
			}
		}
	}

	return S_OK;
}*/

/*

class CursorPos
{
public:
	POINT pos;

	void Draw(HDC hdc)
	{
		int r = 10;
		::MoveToEx(hdc, pos.x - r, pos.y, NULL);
		::LineTo(hdc, pos.x + r, pos.y);

		::MoveToEx(hdc, pos.x, pos.y - r, NULL);
		::LineTo(hdc, pos.x, pos.y + r);
	}

};

static CInput* g_input = NULL;
static CursorPos cursor;
static Draw* draw = NULL;
bool windowmode = true;	//ウィンドウモードの場合はマウス位置をAPIから取得する

CUSTOMVERTEX v[4] = {
	{100.0f,200.0f,0.0f,1.0f,0xffffffff,200.0f,200.0f},
	{100.0f,100.0f,0.0f,1.0f,0xffffffff,200.0f,100.0f},
	{200.0f,200.0f,0.0f,1.0f,0xffffffff,100.0f,200.0f},
	{200.0f,100.0f,0.0f,1.0f,0xffffffff,100.0f,100.0f}
};

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPInst,
	LPSTR lpCmd,
	int nCmd)
{
	//ウィンドウクラスの登録
	WNDCLASSEX wcex;// = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,hInst,NULL,NULL,NULL,NULL,_T("My Window"),NULL };
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc		= MsgProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName	= CLASSNAME;

	if (!RegisterClassEx(&wcex))return FALSE;

	//ウィンドウ作成
	HWND hwnd = CreateWindow(CLASSNAME, 
							_T("3D_Game_PG"),
							WS_OVERLAPPEDWINDOW, 
							CW_USEDEFAULT, 0, 
							1080, 720, 
							NULL, NULL, hInst, NULL);

	if (!hwnd)return FALSE;



	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	if (SUCCEEDED(InitD3D(hwnd))) {

		//タイマーセット
		SetTimer(hwnd, 1, 1, NULL);

		//ウィンドウ表示
		ShowWindow(hwnd, nCmd);
		UpdateWindow(hwnd);

		g_input = new CInput();
		g_input->Create(hwnd);
		g_input->Mouse()->SetWindowMode(windowmode);

		HRESULT hr;
		IDirect3DVertexBuffer9* pVertex;
		hr = g_pd3dDevice->CreateVertexBuffer(
			sizeof(CUSTOMVERTEX) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_CUSTOM,
			D3DPOOL_MANAGED,
			&pVertex,
			NULL);

		void* pData;
		hr = pVertex->Lock(0,
			sizeof(CUSTOMVERTEX) * 4, (void**)&pData,
			0);
		if (hr == D3D_OK) {
			memcpy(pData, v,
				sizeof(CUSTOMVERTEX) * 4);
				pVertex->Unlock();
		}

		g_pd3dDevice->BeginScene();
		g_pd3dDevice->SetStreamSource(0, pVertex, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(FVF_CUSTOM);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
		g_pd3dDevice->EndScene();

		MSG msg = { };

		//メインメッセージループ
		while (msg.message!=WM_QUIT)
		{
			// アプリケーションに送られてくるメッセージをメッセージキューから取得する
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				DispatchMessage(&msg);	// アプリケーションの各ウィンドウプロシージャにメッセージを転送する
			}
			// メッセージ処理をしていないとき
			else {
				//（ここにDirectXの処理を書く）
			}
			//TranslateMessage(&msg);
			//DispatchMessage(&msg);
		}
	}
	//Cleanup();

	return (int)msg.wParam;
}


//画面がちらつくのでダブルバッファを用意
class DoubleBuffer
{
	BYTE* buff;
	HBITMAP hBmp;

public:
	DoubleBuffer()
	{
		buff = NULL;
		hBmp = NULL;
	}
	~DoubleBuffer()
	{
		Release();
	}

	HBITMAP BitmapHandle() { return hBmp; }

	void Create(int w, int h)
	{
		BITMAPINFO bmi;
		bmi.bmiHeader.biSize = sizeof(bmi);
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = -h;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 0;
		bmi.bmiHeader.biXPelsPerMeter = 96;
		bmi.bmiHeader.biYPelsPerMeter = 96;
		bmi.bmiHeader.biClrUsed = 0;
		bmi.bmiHeader.biClrImportant = 0;

		hBmp = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&buff, NULL, 0);

		//背景を白で初期化
		/*
		ハンドルされない例外が 0x0F223E4C (vcruntime140d.dll) で発生しました
		(3D_Game_PG.exe 内): 0xC000041D: ユーザー コールバック中に未処理の
		例外が発生しました。
		解決した
		*//*
		memset(buff, 0xffffffff, 4 * w * h);
	}

	void Release()
	{
		if (hBmp) {
			::DeleteObject(hBmp);
			hBmp = NULL;
			buff = NULL;
		}
	}
};

void Cleanup() {
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

void Render() {
	if (NULL == g_pd3dDevice)
		return;

	//Clear the bakbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//Begin the Scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		//Rendering of Scene objects can happen here

		//End the scene
		g_pd3dDevice->EndScene();
	}

	//Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT InitD3D(HWND hwnd) {

	//IDirect3D9コンポーネントの取得
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return FALSE;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	//画面の大きさ
	d3dpp.BackBufferWidth = 1080;
	d3dpp.BackBufferHeight = 720;
	
	//バックバッファの数
	d3dpp.BackBufferCount = 1;
	
	//有効にすると「ジャギ消し効果」「アンチエイリアス」がかかる
	//対応していない場合があるので、Defaultにしておく。
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	//マルチサンプルの品質レベル
	//MultiSampleTypeがNONEの場合、0で大丈夫
	d3dpp.MultiSampleQuality = 0;

	//フロントバッファとバックバッファの切り替え方法
	//今回のは、ディスプレイドライバが自動判断する
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//描写ウィンドウハンドルの指定
	d3dpp.hDeviceWindow = NULL;

	//スクリーンモードの指定
	//TRUE：フルスクリーン FALSE:ウィンドウ
	d3dpp.Windowed = TRUE;

	//深度ステンシルバッファの設定
	//TRUEなら3Dになる
	d3dpp.EnableAutoDepthStencil =TRUE;

	//ステンシルバッファのフォーマットを指定
	//EnableAutoDepthStencilがFALSEだと無視される
	//TRUEの場合D3DFORMAT列挙型で指定する必要がある
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//バックバッファからフロントバッファへ転送する時の機能の設定
	//今はとりあえず0
	d3dpp.Flags = 0;

	//フルスクリーンのリフレッシュレートを指定
	//ウィンドウだと0にする必要がある
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	
	//スワップの書き換えタイミングを設定する
	//タイミングは垂直回帰線間隔を待つか待たないかがある。
	//待つ場合は、テアリングが出るのを防ぐ
	//待たない場合は、描写が最速になる
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	HRESULT hr;
	if (FAILED(hr = g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hwnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pd3dDevice))) {
		return E_FAIL;
	}

	/*if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, 
									D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pd3dDevice))) {
		return E_FAIL;
	}*//*

	return S_OK;
}



LRESULT WINAPI MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg) 
	{
	case WM_MOUSEMOVE:
		if (g_input) {
			if (windowmode) {
				g_input->Mouse()->SetCursorPos(LOWORD(lParam), HIWORD(lParam));
			}
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	case WM_TIMER:
		if (g_input) {
			g_input->InputUpdate();

			CInputKeyboard* keyboard = g_input->Keyboard();
			CInputMouse* mouse = g_input->Mouse();

			cursor.pos.x = (int)(mouse->PosX());
			cursor.pos.y = (int)(mouse->PosY());
		}

		//ウィンドウの再描画を要求(WM_PAINTが呼ばれる)
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		
		RECT rect;
		GetClientRect(hwnd, &rect);
		//ちらつき防止のためダブルバッファを作る
			//(※ただし、このコード例は画面全範囲を毎回作るのでパフォーマンスが悪いです)
		DoubleBuffer db;
		db.Create(rect.right - rect.left, rect.bottom - rect.top);
		HDC hdcDoubleBuffer = CreateCompatibleDC(hdc);
		SelectObject(hdcDoubleBuffer, db.BitmapHandle());

		//描画(ダブルバッファへ)
		cursor.Draw(hdcDoubleBuffer);
		
		//説明書き
		{

			int linecount = 0;
			TCHAR text[1000];
			ZeroMemory(text, sizeof(text));
			wsprintf(text, TEXT("矢印キー、マウスクリックで赤い丸が動きます"));
			//TextOut(hdcDoubleBuffer, 0, 20 * linecount, text, wcexslen(text));
			linecount++;

			ZeroMemory(text, sizeof(text));
			wsprintf(text, TEXT("ZXCVキーで丸の色が変わります"));
			//TextOut(hdcDoubleBuffer, 0, 20 * linecount, text, wcexslen(text));
			linecount++;
		}

		//ダブルバッファからウィンドウの画面へコピー
		::BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcDoubleBuffer, 0, 0, SRCCOPY);

		DeleteObject(hdcDoubleBuffer);

		EndPaint(hwnd, &ps);
	}
		//Render();
		//ValidateRect(hwnd, NULL);
		//return 0;
		break;
	case WM_DESTROY:
		MessageBox(hwnd, TEXT("終わるヨー"),
			TEXT("Kitty"), MB_ICONINFORMATION);
		if (g_input) {
			g_input->Release();
			delete g_input;
			g_input = NULL;
		}
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);

	}
	return 0;
}*/



/*//ウィンドウフル画面表示
HRESULT InitD3D_Full (HWND hwnd) {
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DDISPLAYMODE dispmode;
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dispmode);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = FALSE;
	d3dpp.BackBufferWidth = 1920;
	d3dpp.BackBufferHeight = 1080;
	//d3dpp.BackBufferWidth = dispmode.Width;
	//d3dpp.BackBufferHeight = dispmode.Height;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = dispmode.Format;
	d3dpp.FullScreen_RefreshRateInHz = dispmode.RefreshRate;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pd3dDevice))) {
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pd3dDevice))) {
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}*/