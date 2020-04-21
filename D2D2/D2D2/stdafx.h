#pragma once
//미리 컴파일 헤더
#ifdef _DEBUG //정의가 되어있을때만 한다 == 디버깅 모드에서만 하겠다
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") // 테스트용 콘솔창 나오게 할수있다.
#endif
//Window
#include <Windows.h>
#include <assert.h>

//STL
#include <iostream>
#include <vector>
//DirectX
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h> //window 10 이후로는 없어졌지만 넣겠다.
//전처리기 문법 
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

typedef unsigned int uint;

//Macro Function
#define SAFE_DELETE(p){ if(p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[] (p); (p)= nullptr; } }
#define SAFE_RELEASE(p) { if(p){ (p)->Release(); (p) = nullptr;} }
//framework
#include "Settings.h"