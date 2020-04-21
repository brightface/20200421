#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

Execute::Execute()
{
	graphics = new Graphics();
	graphics->Initialize();
	graphics->CreateBackBuffer(static_cast<uint>(Settings::Get().GetWidth()), static_cast<uint>( Settings::Get().GetHeight()));

	//vertex data
	{
		vertices = new vertexcolor[4];
		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		vertices[1].position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
		vertices[1].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[2].position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
		vertices[2].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		vertices[3].position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
		vertices[3].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);


	}
	//gpu �� �ֱ����ؼ� ���۸� ����
	//vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE; //���� �Ұ� �б⸸ ���� 
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���� �����Ұ��̳�
		desc.ByteWidth = sizeof(vertexcolor) * 6;

		D3D11_SUBRESOURCE_DATA sub_data; //cpu�����͸� gpu�� �����ϴ°�
		ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = vertices;

		auto hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &vertex_buffer );
		assert((SUCCEEDED(hr)));
	}

	//Index data
	{
		indices = new uint[6]{0,1,2,2,1,3};
	}

	//Index Buffer
	{
D3D11_BUFFER_DESC desc;
ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
desc.Usage = D3D11_USAGE_IMMUTABLE; // gpu�� �б⸸ �����ϴ�. cpu�� ���� ��ü�� �ȵȴ�.
desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
desc.ByteWidth = sizeof(uint) * 6;
//�ΰ����� ���� ����Ÿ ��������

D3D11_SUBRESOURCE_DATA sub_data;
ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
sub_data.pSysMem = indices; //�ý��۸޸𸮿��ٰ� �δ��̽��� ����
//������� �˸��̸� �� �������.

auto hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &index_buffer);
assert(SUCCEEDED(hr));
	}

	//Vertex Shader
	{
	auto hr = D3DX11CompileFromFileA
	(
		"Color.hlsl", //��ó������
		nullptr,
		nullptr,
		"VS",
		"vs_5_0", //shader version , 6_4 ���� ����
		0,
		0,//������ ���� flag�� ���´�.
		nullptr,
		&vs_blob, // 2������
		nullptr,
		nullptr //������ ������ �������� ���Ϲް� �Ǿ��ִ�.
	);
	assert(SUCCEEDED(hr));
	//D3DX11�� �����ϴ� �Լ����� �ֽ� DIRECTX SDK���� �������� �ʴ´�.

	hr = graphics->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vertex_shader);
	assert(SUCCEEDED(hr));
	}
	//input layout
	{
		D3D11_INPUT_ELEMENT_DESC layout_desc[]
		{	//0~ 444 /11  / 12~ /instance input data ȭ�鿡 �Ȱ��� Ǯ �� , 
			{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0  },
			{"COLOR", 0,DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0  },
		};

		auto hr = graphics->GetDevice()->CreateInputLayout(layout_desc, 2, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout);
		assert(SUCCEEDED(hr));
	}

	//Pixel Shader
	{
		auto hr = D3DX11CompileFromFileA
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			nullptr,
			&ps_blob, //binary Large object
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &pixel_shader);
		assert(SUCCEEDED(hr));
		//blob data�� pixelshader�� ���� ���� ��������
	}

	//create world view projection
	{
		D3DXMatrixIdentity(&world); // 1/500
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&projection); //�������
		//��1 �չ��� , �߰� 1 ������
		D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 1), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0, 1);
		//�������� , ��������
		//3D�� ���� ���δ�. ��������
		//��������, 2D, UI, Invectory, �ָ� �����̰� ����

		//<<�� bit������, shift�����ڰ� �ƴϴ�.
		std::cout << "view matrix" << std::endl;
		std::cout << view._11 << " " << view._12 << " " << view._13 << " " << view._14 << std::endl;
		std::cout << view._21 << " " << view._22 << " " << view._23 << " " << view._24 << std::endl;
		std::cout << view._31 << " " << view._32 << " " << view._33 << " " << view._34 << std::endl;
		std::cout << view._41 << " " << view._42 << " " << view._43 << " " << view._44 << std::endl;

		std::cout << std::endl;

		std::cout << "projection matrix" << std::endl;
		std::cout << projection._11 << " " << projection._12 << " " << projection._13 << " " << projection._14 << std::endl;
		std::cout << projection._21 << " " << projection._22 << " " << projection._23 << " " << projection._24 << std::endl;
		std::cout << projection._31 << " " << projection._32 << " " << projection._33 << " " << projection._34 << std::endl;
		std::cout << projection._41 << " " << projection._42 << " " << projection._43 << " " << projection._44 << std::endl;
	
		//World
		D3DXMATRIX S;
		D3DXMatrixScaling(&world, 100, 100, 1); //�������� ������ �β� ���� 0�� ���� �ȵ�
		//D3DXMatrixTranslation(&world, 100, 100, 0); //ũ�Ⱑ �������.
	
		std::cout << std::endl;

		std::cout << "scale matrix" << std::endl;
		std::cout << S._11 << " " << S._12 << " " << S._13 << " " << S._14 << std::endl;
		std::cout << S._21 << " " << S._22 << " " << S._23 << " " << S._24 << std::endl;
		std::cout << S._31 << " " << S._32 << " " << S._33 << " " << S._34 << std::endl;
		std::cout << S._41 << " " << S._42 << " " << S._43 << " " << S._44 << std::endl;

		D3DXMATRIX T;
		std::cout << T._11 << " " << T._12 << " " << T._13 << " " << T._14 << std::endl;
		std::cout << T._21 << " " << T._22 << " " << T._23 << " " << T._24 << std::endl;
		std::cout << T._31 << " " << T._32 << " " << T._33 << " " << T._34 << std::endl;
		std::cout << T._41 << " " << T._42 << " " << T._43 << " " << T._44 << std::endl;

		D3DXMATRIX R;
		//������ ȸ����ų��, �ޱ�(����): r�⺻ ������,f�Ⱥپ�������
		D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));
		//z�� ȸ�����Ѿ� xy����� ���ư���.

		//����� ��ȯ��Ģ�� �������� �ʴ´�.
		//��*��*��*��*��
		//s *r * T * R * p
		//������ ��� * �������(r - ������ ����) *�̵���� * ������� * �θ����

		//world = S *R* T;
		world = world * R;
	}

	

	//Create Constant Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		//cpu���� ���ְ� gpu���� �о�� �ؼ� dynamic
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TRANSFORM_DATA);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		//subresource �� �����Ӹ��� 
		auto hr = graphics->GetDevice()->CreateBuffer(&desc, nullptr, &gpu_buffer);
		assert(SUCCEEDED(hr));
	}

	//Create Rasterizer state
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		//IA, RS,OM stage �ڵ��Ұ� , ���ø� �ϴ°�, �귯���� ���ٲ�
		desc.FillMode = D3D11_FILL_SOLID; //D3D11_FILL_WIREFRAME
		desc.CullMode = D3D11_CULL_BACK; //�ø��� ��� �Ұ��̳�
		desc.FrontCounterClockwise = false;

		//culling ī�޶� ������ �ʴ°� �� �����.
		//cliping �׸��Ŀ� �ڸ���. ����� �߻� ���ݴ�.

		auto hr = graphics->GetDevice()->CreateRasterizerState(&desc, &rasterizer_state);
		assert(SUCCEEDED(hr));

	}
	//Create shader resource view
	{
		auto hr = D3DX11CreateShaderResourceViewFromFile
		(
			graphics->GetDevice(), 
			"tree.png",
			nullptr,
			nullptr,
			&shader_resource,
			nullptr
		);
	}
}



Execute::~Execute()
{	
	SAFE_RELEASE(shader_resource);
	SAFE_RELEASE(pixel_shader);
	SAFE_RELEASE(ps_blob);

	SAFE_RELEASE(input_layout);
	//cominterface �� ��������� delete�� ����� �ȵ� release ���ؾߵ�
	SAFE_RELEASE(vertex_shader);
	SAFE_RELEASE(vs_blob);
	
	SAFE_RELEASE(index_buffer);
	SAFE_DELETE_ARRAY(indices);
	
	SAFE_RELEASE(vertex_buffer);
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE(graphics);
}

void Execute::Update()
{
	/*world._11 = 50;
	world._22 = 50;
	
	world._41 = 100;
	world._42 = 100;*///���� world��.

	//D3DZMATRIX - �� �켱 ���
	//GPU - shader - matrix - �� �켱 ���

	static float radian = 0.0f; //���������� 0.0���� �ʱ�ȭ �ڵ����� �ȴ�.
	radian += 0.01f;
	D3DXMATRIX P;
	D3DXMatrixRotationZ(&P, radian);
	//�θ������ ��� ���󰣴�. �ڽĵ��� 

	D3DXMatrixTranspose(&cpu_buffer.world, &world);
	//cpu_buffer.world = world;
	D3DXMatrixTranspose(&cpu_buffer.view, &view);
		//cpu_buffer.view = view;
	D3DXMatrixTranspose(&cpu_buffer.projection, &projection);
		//cpu_buffer.projection = projection;

	D3D11_MAPPED_SUBRESOURCE mapped_subresource; //������ 
	graphics->GetDeviceContext()->Map
	(
		gpu_buffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mapped_subresource
	); //gpu�ϴ°��� GETdevicecontext

	memcpy(mapped_subresource.pData, &cpu_buffer, sizeof(TRANSFORM_DATA));

	graphics->GetDeviceContext()->Unmap(gpu_buffer, 0);

}

void Execute::Rendor()
{
	uint stride = sizeof(vertexcolor); // ����// ����
	uint offset = 0;//������ 
	graphics->Begin();
	{
		//IA
		graphics->GetDeviceContext()->IAGetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout);
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //��� ������ �˷���
		graphics->GetDeviceContext()->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
		//index Buffer�� IA�� ����. ������� ������� ȣ��Ǵ°� ����
		//

		//VS// ���� 10���� 10������. /GPU�� ����ó��
		graphics->GetDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);
		graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &gpu_buffer);

		//RS
		graphics->GetDeviceContext()->RSSetState(rasterizer_state);

		//PS , grapic ���� CPU deviceContext
		graphics->GetDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);
		graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &shader_resource);
		//indexbuffer ������ drawIndexed�� �ٲ��.
		//graphics->GetDeviceContext()->Draw(3, 0); //3��, 0���� �׸���(��ŸƮ����)
		graphics->GetDeviceContext()->DrawIndexed(6,0, 0);
	}
	//������ �׸��͵��� ���� ���� ���̿��� ������ �ȴ�.
	//��ȭ�� ����, ������Ʈ �ϴ°� �Ű澵 �ʿ� ����.
	graphics->End();
}

//		0

//0		0
//������ ������ ���� �̾ ���� ä���� �̾߱����� 
//���������� ������Ѵ�.


