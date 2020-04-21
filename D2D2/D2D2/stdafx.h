#pragma once
//�̸� ������ ���
#ifdef _DEBUG //���ǰ� �Ǿ��������� �Ѵ� == ����� ��忡���� �ϰڴ�
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") // �׽�Ʈ�� �ܼ�â ������ �Ҽ��ִ�.
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
#include <D3DX11async.h> //window 10 ���ķδ� ���������� �ְڴ�.
//��ó���� ���� 
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