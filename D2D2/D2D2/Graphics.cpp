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
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));//메모리 자체를 비운다.
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60; // 화면주사율 얼마나 빈번하게 새롭게 하냐 분자
	desc.BufferDesc.RefreshRate.Denominator = 1; //분모
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //8비트 256 / U normalize
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//이게 안되니까 렌더 타겟뷰를 만들수가 없다. 이게 안되니까 DESC만들어게 출력용이 아니니
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
		feature_levels.data(), //벡터의 시작주소 반환
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
	//화가가 판넬 만들었으면 종이를 만들어야지

	//RendorTargetView 가 도화지 역할을 한다.

	ID3D11Texture2D* back_buffer = nullptr;
	hr = swap_chain->GetBuffer //자기가 가지고 있는 내부의 버퍼를 꺼내주는 함수
	(
		0,
		__uuidof(ID3D11Texture2D), //IID,uuid,guid
		reinterpret_cast<void**>(&back_buffer)
	); //자기가 가지고 있는정보를 꺼내준다.
	assert(SUCCEEDED(hr));
	
	//도화지를 바로 만들수가 없다.
	hr = device->CreateRenderTargetView
	(
		back_buffer,
		nullptr,
		&render_target_view
	);
	assert(SUCCEEDED(hr));
	//backbuffer 관리하는것 끝났어

	viewport.TopLeftX = 0.0f; //시작점
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
	//double buffering 사용중 앞면에서 보여준다. 비긴은 
	//그리기를 시작할때 호출되기에 버퍼 세팅과 초기화 작업에 들어가야 한다.
	//그리고 그리기전에 머 있을수 있으니까 클리어먼저 해야한다.
	//ID3D11RenderTargetView* rtvs[] = { render_target_view; }
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr); //랜더링에 관련된 것은 무조건 device_context , 자원만들때는 device 사용 
	//OM : output merger stage , RenderTargetview 를 의미하는 도화지 역할을 한다.
	//begin은 후면을 의미한다.
	//색을 어떻게 섞을것인가?
	//num과 복수형은 몇개냐 뭍는것 매개변수시
	device_context->RSSetViewports(1, &viewport);
		//보여질 영역 
	device_context->ClearRenderTargetView(render_target_view, clear_color);
	
}

void Graphics::End()
{
	//전면으로 내보내주는것
	auto hr = swap_chain -> Present(1,0);
	assert(SUCCEEDED(hr)); //성공했는지 확인
}

//ID3D11Resource

//ID3D11Buffer 구조체 자료형 하나밖에 없어 데이터 크게 관련이 없어
//ID3D11TextureID  이미지 자원들
//ID3D11Texture2D, 사용범위가 굉장히 광범위 하다. 어떤 데이터를 그릴수 있지 
//ID3D11Textrue3D // 이미지화 되있는 자원들. 사용용도가 명확하지가 않아 
//그린다는 이야기인가 만들어진것을 가져온것다는 이야기인가 구분이안돼
//그것때문에 나온게 resuorce view 자원 뷰 사용용도 명확히
//Resource view 종류 : ID3D11RenderTargetView 화면에 그리기위한것, ID3D11ShaderResourceView : 만들어진것을 넘기기 위한 것, ID3D11render와 비슷, 쓰기용 읽기용 다되는놈  

