#include "Input.h"

CInputMouse::CInputMouse()
{
	m_hWnd = NULL;
	m_pDIMouse = NULL; 
	m_wndHgt = NULL;
	m_wndWid = NULL;
	m_posX = 0;
	m_posY = 0;
	m_LDown = FALSE;
	m_RDown = FALSE;
	m_MDown = FALSE;
	m_LAction = FALSE;
	m_RAction = FALSE;
	m_MAction = FALSE;

	m_windowMode = TRUE;
}

//�}�E�X�f�o�C�X�̍쐬
bool CInputMouse::Create(IDirectInput8* pDInput, HWND hWnd)
{
	HRESULT hr;

	if (!pDInput) {
		return FALSE;
	}

	m_hWnd = hWnd;
	RECT rect;
	GetClientRect(m_hWnd, &rect);
	m_wndWid = rect.right - rect.left;
	m_wndHgt = rect.bottom - rect.top;
	m_posX = m_wndWid / 2;
	m_posY = m_wndHgt / 2;

	//�}�E�X�f�o�C�X���쐬
	hr = pDInput->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);
	if (FAILED(hr)) {
		return FALSE;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr)) {
		return FALSE;
	}

	//�o�b�t�@�T�C�Y�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = 1000;
	hr = m_pDIMouse->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
	if (FAILED(hr)) {
		return FALSE;
	}

	//�������[�h�̐ݒ�
	hr = m_pDIMouse->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return FALSE;
	}

	//���͂�������
	m_pDIMouse->Acquire();

	return TRUE;
}

//�}�E�X�̓��͏�Ԃ��X�V
void CInputMouse::Update()
{
	//���Z�b�g����B���̂��߃N���b�N��UpdateMouse()������ĂԑO�ɏ������Ȃ���΂Ȃ�Ȃ��B
	m_LAction = FALSE;
	m_RAction = FALSE;
	m_MAction = FALSE;

	DIDEVICEOBJECTDATA od;
	DWORD dwItems = 1;
	HRESULT hr;
	while (TRUE) {
		hr = m_pDIMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);

		if (hr == DIERR_INPUTLOST) {
			m_pDIMouse->Acquire();
		}
		else
			if (dwItems == 0 || FAILED(hr)) {

				if (hr == DIERR_NOTACQUIRED) {
					m_pDIMouse->Acquire();
				}

				break;
			}
			else {

				switch (od.dwOfs) {
				case DIMOFS_X:
					if (!m_windowMode) {
						m_posX += (int)od.dwData;
						m_posX = max(0, min(m_posX, m_wndWid));//�E�B���h�E����͂ݏo�Ȃ��悤����
					}
					break;
				case DIMOFS_Y:
					if (!m_windowMode) {
						m_posY += (int)od.dwData;
						m_posY = max(0, min(m_posY, m_wndHgt));
					}
					break;
				case DIMOFS_BUTTON0://���{�^��
					m_LDown = (od.dwData & 0x80) ? TRUE : FALSE;
					if (m_LDown) { m_LAction = TRUE; }
					break;
				case DIMOFS_BUTTON1://�E�{�^��
					m_RDown = (od.dwData & 0x80) ? TRUE : FALSE;
					if (m_RDown) { m_RAction = TRUE; }
					break;
				case DIMOFS_BUTTON2://���{�^��
					m_MDown = (od.dwData & 0x80) ? TRUE : FALSE;
					if (m_MDown) { m_MAction = TRUE; }
					break;
				}
			}
	}
}


//�}�E�X�f�o�C�X�̉��
void CInputMouse::Release()
{
	if (m_pDIMouse != NULL) {
		m_pDIMouse->Unacquire();
		m_pDIMouse->Release();
		m_pDIMouse = NULL;
	}

	m_hWnd = NULL;
	m_posX = 0;
	m_posY = 0;
	m_LDown = FALSE;
	m_RDown = FALSE;
	m_MDown = FALSE;
	m_LAction = FALSE;
	m_RAction = FALSE;
	m_MAction = FALSE;

}