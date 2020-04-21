#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	SAFE_RELEASE(render_target_view);
	SAFE_RELEASE(device);
	SAFE_RELEASE(device_context);
	SAFE_RELEASE(swap_chain);
}

void Graphics::Initialize()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));//�޸� ��ü�� ����.
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60; // ȭ���ֻ��� �󸶳� ����ϰ� ���Ӱ� �ϳ� ����
	desc.BufferDesc.RefreshRate.Denominator = 1; //�и�
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //8��Ʈ 256 / U normalize
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//�̰� �ȵǴϱ� ���� Ÿ�ٺ並 ������� ����. �̰� �ȵǴϱ� DESC������ ��¿��� �ƴϴ�
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.OutputWindow = Settings::Get().GetWindowHandle();
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	std::vector<D3D_FEATURE_LEVEL> feature_levels
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	auto hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		feature_levels.data(), //������ �����ּ� ��ȯ
		feature_levels.size(),
		//4,
		D3D11_SDK_VERSION,
		&desc,
		&swap_chain,
		&device,
		nullptr,
		&device_context
	);
	assert(SUCCEEDED(hr));
}

void Graphics::CreateBackBuffer(const uint& width, const uint& height)
{
	auto hr = swap_chain->ResizeBuffers
	(
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN,
		0
	);
	assert(SUCCEEDED(hr));
	//ȭ���� �ǳ� ��������� ���̸� ��������

	//RendorTargetView �� ��ȭ�� ������ �Ѵ�.

	ID3D11Texture2D* back_buffer = nullptr;
	hr = swap_chain->GetBuffer //�ڱⰡ ������ �ִ� ������ ���۸� �����ִ� �Լ�
	(
		0,
		__uuidof(ID3D11Texture2D), //IID,uuid,guid
		reinterpret_cast<void**>(&back_buffer)
	); //�ڱⰡ ������ �ִ������� �����ش�.
	assert(SUCCEEDED(hr));
	
	//��ȭ���� �ٷ� ������� ����.
	hr = device->CreateRenderTargetView
	(
		back_buffer,
		nullptr,
		&render_target_view
	);
	assert(SUCCEEDED(hr));
	//backbuffer �����ϴ°� ������

	viewport.TopLeftX = 0.0f; //������
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	SAFE_RELEASE(back_buffer);
	/*if(back_buffer != nullptr)
		back_buffer->Release();*/
}

void Graphics::Begin()
{
	//double buffering ����� �ո鿡�� �����ش�. ����� 
	//�׸��⸦ �����Ҷ� ȣ��Ǳ⿡ ���� ���ð� �ʱ�ȭ �۾��� ���� �Ѵ�.
	//�׸��� �׸������� �� ������ �����ϱ� Ŭ������� �ؾ��Ѵ�.
	//ID3D11RenderTargetView* rtvs[] = { render_target_view; }
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr); //�������� ���õ� ���� ������ device_context , �ڿ����鶧�� device ��� 
	//OM : output merger stage , RenderTargetview �� �ǹ��ϴ� ��ȭ�� ������ �Ѵ�.
	//begin�� �ĸ��� �ǹ��Ѵ�.
	//���� ��� �������ΰ�?
	//num�� �������� ��� ���°� �Ű�������
	device_context->RSSetViewports(1, &viewport);
		//������ ���� 
	device_context->ClearRenderTargetView(render_target_view, clear_color);
	
}

void Graphics::End()
{
	//�������� �������ִ°�
	auto hr = swap_chain -> Present(1,0);
	assert(SUCCEEDED(hr)); //�����ߴ��� Ȯ��
}

//ID3D11Resource

//ID3D11Buffer ����ü �ڷ��� �ϳ��ۿ� ���� ������ ũ�� ������ ����
//ID3D11TextureID  �̹��� �ڿ���
//ID3D11Texture2D, �������� ������ ������ �ϴ�. � �����͸� �׸��� ���� 
//ID3D11Textrue3D // �̹���ȭ ���ִ� �ڿ���. ���뵵�� ��Ȯ������ �ʾ� 
//�׸��ٴ� �̾߱��ΰ� ����������� �����°ʹٴ� �̾߱��ΰ� �����̾ȵ�
//�װͶ����� ���°� resuorce view �ڿ� �� ���뵵 ��Ȯ��
//Resource view ���� : ID3D11RenderTargetView ȭ�鿡 �׸������Ѱ�, ID3D11ShaderResourceView : ����������� �ѱ�� ���� ��, ID3D11render�� ���, ����� �б�� �ٵǴ³�  

