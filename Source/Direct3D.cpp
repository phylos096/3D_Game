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

	// Direct3D9�I�u�W�F�N�g�̍쐬	
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//IDirect3D9�R���|�[�l���g�̎擾
	if (NULL == (pD3D9 = Direct3DCreate9(D3D_SDK_VERSION)))return FALSE;

	// �f�B�X�v���C���擾
	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);

	D3DPRESENT_PARAMETERS D3DParam;
	ZeroMemory(&D3DParam, sizeof(D3DParam));
	//��ʂ̑傫��
	D3DParam.BackBufferWidth = Window_Width;
	D3DParam.BackBufferHeight = Window_Height;

	//��ʂ̃t�H�[�}�b�g���
	D3DParam.BackBufferFormat = Display.Format;

	//�o�b�N�o�b�t�@�̐�
	D3DParam.BackBufferCount = 1;

	//�L���ɂ���Ɓu�W���M�������ʁv�u�A���`�G�C���A�X�v��������
	//�Ή����Ă��Ȃ��ꍇ������̂ŁADefault�ɂ��Ă����B 
	D3DParam.MultiSampleType = D3DMULTISAMPLE_NONE;

	//�}���`�T���v���̕i�����x��
	//MultiSampleType��NONE�̏ꍇ�A0�ő��v
	D3DParam.MultiSampleQuality = 0;

	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ����@
	//����̂́A�f�B�X�v���C�h���C�o���������f����
	D3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//�`�ʃE�B���h�E�n���h���̎w��
	D3DParam.hDeviceWindow = hWnd;

	//�X�N���[�����[�h�̎w��
	//TRUE�F�t���X�N���[�� FALSE:�E�B���h�E
	D3DParam.Windowed = TRUE;

	//�[�x�X�e���V���o�b�t�@�̐ݒ�
	//TRUE�Ȃ�3D�ɂȂ�
	D3DParam.EnableAutoDepthStencil = TRUE;

	//�X�e���V���o�b�t�@�̃t�H�[�}�b�g���w��
	//EnableAutoDepthStencil��FALSE���Ɩ��������
	//TRUE�̏ꍇD3DFORMAT�񋓌^�Ŏw�肷��K�v������
	D3DParam.AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;

	//�o�b�N�o�b�t�@����t�����g�o�b�t�@�֓]�����鎞�̋@�\�̐ݒ�
	//���͂Ƃ肠����0
	D3DParam.Flags = 0;

	//�t���X�N���[���̃��t���b�V�����[�g���w��
	//�E�B���h�E����0�ɂ���K�v������
	D3DParam.FullScreen_RefreshRateInHz = 0;//;

	//�X���b�v�̏��������^�C�~���O��ݒ肷�� 
	//�^�C�~���O�͐�����A���Ԋu��҂��҂��Ȃ���������B
	//�҂ꍇ�́A�e�A�����O���o��̂�h��
	//�҂��Ȃ��ꍇ�́A�`�ʂ��ő��ɂȂ�
	D3DParam.PresentationInterval = D3DPRESENT_RATE_DEFAULT;// D3DPRESENT_INTERVAL_DEFAULT;

	// HAL���[�h��3D�f�o�C�X�쐬
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D))) {
		if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D))) {
			// REF���[�h��3D�f�o�C�X�쐬
			if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
			{
				if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
				{
					// 3D�f�o�C�X�쐬���s
					pD3D9->Release();
					return false;
				}
			}
		}
	}
	
	return true;
}

void Direct3D::SetView() {
	//�����̐ݒ�
	pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	//�r���[�ϊ�
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pDevice3D->SetTransform(D3DTS_VIEW, &matView);
	//�ˉe�ϊ�
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, GameAspect, 1.0f, 100.0f);
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);
}