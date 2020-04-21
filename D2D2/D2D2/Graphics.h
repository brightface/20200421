#pragma once
//#include <d3d11.h>

class Graphics final
{
public:
	Graphics();
	~Graphics();

	void Initialize();
	void CreateBackBuffer(const uint &width, const uint& height);
	auto GetDevice()-> ID3D11Device* { return device; }
	auto GetDeviceContext() -> ID3D11DeviceContext* { return device_context; }
	// 같은것
	//auto GetDevice() { return device; }// 같은것 모던 c++에 추가되어서 안써도 같다.
	//ID3D11Device* GetDevice() { return device; }
	

	void Begin();
	void End();

private:
	ID3D11Device* device				= nullptr;
	ID3D11DeviceContext* device_context = nullptr;
	IDXGISwapChain* swap_chain			= nullptr;
	ID3D11RenderTargetView* render_target_view = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	D3DXCOLOR clear_color = 0xff555566; //회색, 흰색이면 Direct연동이 안된것!
};

//DirectX ~ API
//openGL 다양해 모바일도 플렛폼 가지고 있다.
//그럼 왜 이걸 안배워? 기본적으로 WINDOW 편하게 쓸수있다.
// 다양한 플렛폼 사용하니 입문하기가 까다롭다. 코드가 유연
//시스템 자체는 비슷하게 흘러간다.

//GPU : Graphics Process Unit
//gpu코어수가 3000천개 이상 cpu 