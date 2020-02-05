#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS

#define CLASSNAME TEXT("3D_Game")
#define D3D_DEBUG_INFO	// Direct3Dデバックフラグ

#define RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

#define DIRECTINPUT_VERSION 0x0800

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define PLAYER_MOVE_SPEED 0.05

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//IncludeHeader
#include<stdio.h>
#include<iostream>
#include <Windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <comdef.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <string.h>
#include <string>
#include <dxerr.h>
#include <vector>
#include <dinput.h>	//入力

