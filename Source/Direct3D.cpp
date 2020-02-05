#include"Direct3D.h"

Direct3D::Direct3D() {
	pD3D9 = NULL;
	pDevice3D = NULL;
	//g_pDevice = NULL;
	GameAspect = 1.0f;
};

Direct3D::~Direct3D() {
	if (pDevice3D != NULL) pDevice3D->Release();
	if (pD3D9 != NULL)pD3D9->Release();
};

bool Direct3D::Create(HWND hWnd, int Window_Width, int Window_Height) {

	// Direct3D9オブジェクトの作成	
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//IDirect3D9コンポーネントの取得
	if (NULL == (pD3D9 = Direct3DCreate9(D3D_SDK_VERSION)))return FALSE;

	// ディスプレイ情報取得
	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);

	D3DPRESENT_PARAMETERS D3DParam;
	ZeroMemory(&D3DParam, sizeof(D3DParam));
	//画面の大きさ
	D3DParam.BackBufferWidth = Window_Width;
	D3DParam.BackBufferHeight = Window_Height;

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
					return false;
				}
			}
		}
	}
	
	return true;
}

void Direct3D::SetView() {
	//環境光の設定
	pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	//ビュー変換
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pDevice3D->SetTransform(D3DTS_VIEW, &matView);
	//射影変換
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, GameAspect, 1.0f, 100.0f);
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);
}