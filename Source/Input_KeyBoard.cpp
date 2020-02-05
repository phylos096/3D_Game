#include "Input.h"

CInputKeyboard::CInputKeyboard()
{
	m_pDIDevKB = NULL;
	ZeroMemory(m_Keystate, sizeof(m_Keystate));
	ZeroMemory(m_KeyAction, sizeof(m_KeyAction));
}

//キーボードデバイスを作成
bool CInputKeyboard::Create(IDirectInput8* pDInput, HWND hWnd)
{
	HRESULT hr;

	if (!pDInput) {
		return FALSE;
	}

	// キーボードデバイスを作成
	hr = pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevKB, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//データフォーマットの設定
	hr = m_pDIDevKB->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//バッファサイズの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = 1000;
	hr = m_pDIDevKB->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
	if (FAILED(hr)) {
		return FALSE;
	}

	//協調モードの設定
	hr = m_pDIDevKB->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//入力を許可する
	m_pDIDevKB->Acquire();
	return TRUE;
}

//キーボードの入力状態を更新
void CInputKeyboard::Update()
{
	ZeroMemory(m_KeyAction, sizeof(m_KeyAction));

	DIDEVICEOBJECTDATA od;
	DWORD dwItems = 1;
	HRESULT hr;
	while (TRUE) {
		hr = m_pDIDevKB->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);

		if (hr == DIERR_INPUTLOST) {
			m_pDIDevKB->Acquire();
		}
		else
			if (dwItems == 0 || FAILED(hr)) {

				if (hr == DIERR_NOTACQUIRED) {
					m_pDIDevKB->Acquire();
				}

				break;
			}
			else {

				m_Keystate[od.dwOfs] = (od.dwData & 0x80) ? TRUE : FALSE;

				if (m_Keystate[od.dwOfs]) {
					m_KeyAction[od.dwOfs] = TRUE;
				}
			}
	}
}

//キーボードデバイスの解放
void CInputKeyboard::Release()
{
	if (m_pDIDevKB) {
		m_pDIDevKB->Unacquire();
		m_pDIDevKB->Release();
		m_pDIDevKB = NULL;
	}
	ZeroMemory(m_Keystate, sizeof(m_Keystate));
	ZeroMemory(m_KeyAction, sizeof(m_KeyAction));
}