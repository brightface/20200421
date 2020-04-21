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
	// ������
	//auto GetDevice() { return device; }// ������ ��� c++�� �߰��Ǿ �Ƚᵵ ����.
	//ID3D11Device* GetDevice() { return device; }
	

	void Begin();
	void End();

private:
	ID3D11Device* device				= nullptr;
	ID3D11DeviceContext* device_context = nullptr;
	IDXGISwapChain* swap_chain			= nullptr;
	ID3D11RenderTargetView* render_target_view = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	D3DXCOLOR clear_color = 0xff555566; //ȸ��, ����̸� Direct������ �ȵȰ�!
};

//DirectX ~ API
//openGL �پ��� ����ϵ� �÷��� ������ �ִ�.
//�׷� �� �̰� �ȹ��? �⺻������ WINDOW ���ϰ� �����ִ�.
// �پ��� �÷��� ����ϴ� �Թ��ϱⰡ ��ٷӴ�. �ڵ尡 ����
//�ý��� ��ü�� ����ϰ� �귯����.

//GPU : Graphics Process Unit
//gpu�ھ���� 3000õ�� �̻� cpu 