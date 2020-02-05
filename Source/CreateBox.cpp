#include "CreateBox.h"

BOX3D::BOX3D() {
	for (byte box3d_i = 0; box3d_i < 6; box3d_i++) {
		for (byte box3d_j = 0; box3d_j < 4; box3d_j++) {
			X[box3d_i][box3d_j] = 0.0f;
			Y[box3d_i][box3d_j] = 0.0f;
			Z[box3d_i][box3d_j] = 0.0f;
			Color[box3d_i][box3d_j] = 0xffffffff;
		}
	}
	ZeroMemory(tmpPosition, sizeof(D3DXVECTOR3));
};

BOX3D::~BOX3D() {

};

/// <summary>
/// 立方体の中心座標を入力する
/// </summary>
void BOX3D::CreateBOX(float x, float y, float z, float length) {
	
	//各頂点の座標を格納する
	for (byte box3d_i = 0; box3d_i < 6; box3d_i++) {
		for (byte box3d_j = 0; box3d_j < 4; box3d_j++) {
			switch (box3d_i)
			{
			case 0:
				tmpPosition = Calculation(BOX_FRONT, box3d_j);
				break;
			case 1:
				tmpPosition = Calculation(BOX_RIGHT, box3d_j);
				break;
			case 2:
				tmpPosition = Calculation(BOX_UP, box3d_j);
				break;
			case 3:
				tmpPosition = Calculation(BOX_LEFT, box3d_j);
				break;
			case 4:
				tmpPosition = Calculation(BOX_DOWN, box3d_j);
				break;
			case 5:
				tmpPosition = Calculation(BOX_BACK, box3d_j);
				break;
			}
			X[box3d_i][box3d_j] = x + length / 2 * tmpPosition.x;
			Y[box3d_i][box3d_j] = y + length / 2 * tmpPosition.y;
			Z[box3d_i][box3d_j] = z + length / 2 * tmpPosition.z;
		}
	}
	tmpPosition = D3DXVECTOR3(x, y, z);
};

void BOX3D::SetUpMatrices(IDirect3DDevice9* pDevice3D,float x,float y,float z) {
	D3DXMATRIX      matView;
	D3DXMATRIX      matProj;
	D3DXMATRIX      w;

	//D3DXMatrixRotationAxis(&w, &tmpPosition, timeGetTime()); // 任意の軸を回転軸にして回転する行列を作成する。 システム時刻をミリ秒単位で取得

	D3DXMatrixTranslation(&matView, tmpPosition.x, tmpPosition.y, tmpPosition.z); // オフセットを指定して行列を作成する。

	//matView = w * matView;
	pDevice3D->SetTransform(D3DTS_VIEW, &matView);

	//透視変換の設定// 視野に基づいて、左手座標系パースペクティブ射影行列を作成する
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f), 1.0f, -300, 300); 
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);
}


void BOX3D::Draw(IDirect3DDevice9* pDevice3D) {
	SetUpMatrices(pDevice3D,0, 0, 0);
	pDevice3D->SetFVF(D3DFVF_VERTEX);
	for (byte box_i = 0; box_i < 6; box_i++) {
		//for (byte box_j = 0; box_j < 4; box_j++) {
			pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (X[box_i], Y[box_i], Z[box_i],Color[box_i]), sizeof(D3DXVECTOR3));
		//}
	}
}

D3DXVECTOR3 BOX3D::Calculation(const char* str,byte i) {

	byte tmpFlag[3] = { -1 };
	char tmpChar = str[i];
	switch (tmpChar) {
	case '0':
	case '8':

		break;
	case '1':
	case '9':
		tmpFlag[2] = 1;
		break;
	case '2':
	case 'A':
		tmpFlag[1] = 1;
		break;
	case '3':
	case 'B':
		tmpFlag[2] = 1;
		tmpFlag[1] = 1;
		break;
	case '4':
	case 'C':
		tmpFlag[0] = 1;
		break;
	case '5':
	case 'D':
		tmpFlag[2] = 1;
		tmpFlag[0] = 1;
		break;
	case '6':
	case 'E':
		tmpFlag[1] = 1;
		tmpFlag[0] = 1;
		break;
	case '7':
	case 'F':
		tmpFlag[2] = 1;
		tmpFlag[1] = 1;
		tmpFlag[0] = 1;
		break;
	defalut:
		break;
	}

	return { (float)tmpFlag[0],(float)tmpFlag[1],(float)tmpFlag[2] };
}


/*  
1	50,50,50

2	50,50,-50

3	50,-50,50

4	-50,50,50

5	50,-50,-50

6	-50,50,-50

7	-50,-50,50

8	-50,-50,-50

7341 3512 8573 4678 6285 2614

//先頭に0を足す
001 101 011 111 -> 0001 0101 0011 0111 -> 1537(5431)
101 100 111 110 -> 0101 0100 0111 0110 -> 5476(21622)
000 100 001 101 -> 0000 0100 0001 0101 -> 0415(1045)
011 010 001 000 -> 0011 0010 0001 0000 -> 3210(12816)
010 110 000 100 -> 0010 0110 0000 0100 -> 3604(13828)
110 010 111 011 -> 0110 0010 0111 0011 -> 6273(25203)

//先頭に1を足す
001 101 011 111 -> 1001 1101 1011 1111 -> 9DBF(40383)
101 100 111 110 -> 1101 1100 1111 1110 -> DCFE(56574)
000 100 001 101 -> 1000 1100 1001 1101 -> 8C9D(35997)
011 010 001 000 -> 1011 1010 1001 1000 -> BA98(47768)
010 110 000 100 -> 1010 1110 1000 1100 -> AE8C(44684)
110 010 111 011 -> 1110 1010 1111 1011 -> EAFB(60155)

  */