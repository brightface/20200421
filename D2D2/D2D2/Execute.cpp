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
	//gpu 에 넣기위해서 버퍼를 만듬
	//vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE; //쓰기 불가 읽기만 가능 
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//어디다 연결할것이냐
		desc.ByteWidth = sizeof(vertexcolor) * 6;

		D3D11_SUBRESOURCE_DATA sub_data; //cpu데이터를 gpu에 연결하는것
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
desc.Usage = D3D11_USAGE_IMMUTABLE; // gpu가 읽기만 가능하다. cpu는 접근 자체가 안된다.
desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
desc.ByteWidth = sizeof(uint) * 6;
//부가정보 서블릿 데이타 만들어야지

D3D11_SUBRESOURCE_DATA sub_data;
ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
sub_data.pSysMem = indices; //시스템메모리에다가 인다이스를 연결
//껍데기와 알맹이를 다 만들었다.

auto hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &index_buffer);
assert(SUCCEEDED(hr));
	}

	//Vertex Shader
	{
	auto hr = D3DX11CompileFromFileA
	(
		"Color.hlsl", //맨처음파일
		nullptr,
		nullptr,
		"VS",
		"vs_5_0", //shader version , 6_4 까지 나옴
		0,
		0,//오래된 구문 flag로 막는다.
		nullptr,
		&vs_blob, // 2진파일
		nullptr,
		nullptr //어차피 위에서 에러나면 리턴받게 되어있다.
	);
	assert(SUCCEEDED(hr));
	//D3DX11로 시작하는 함수들은 최신 DIRECTX SDK에는 지원하지 않는다.

	hr = graphics->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vertex_shader);
	assert(SUCCEEDED(hr));
	}
	//input layout
	{
		D3D11_INPUT_ELEMENT_DESC layout_desc[]
		{	//0~ 444 /11  / 12~ /instance input data 화면에 똑같은 풀 깔때 , 
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
		//blob data와 pixelshader를 만듬 이제 지워야지
	}

	//create world view projection
	{
		D3DXMatrixIdentity(&world); // 1/500
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&projection); //단위행렬
		//끝1 앞방향 , 중간 1 위방향
		D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 1), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0, 1);
		//원근투영 , 직교투영
		//3D에 많이 쓰인다. 원근투영
		//직교투영, 2D, UI, Invectory, 멀리 가까이가 없어

		//<<는 bit연산자, shift연산자가 아니다.
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
		D3DXMatrixScaling(&world, 100, 100, 1); //마지막은 종이의 두께 따라서 0이 오면 안돼
		//D3DXMatrixTranslation(&world, 100, 100, 0); //크기가 사라졌다.
	
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
		//위에것 회전시킬것, 앵글(라디안): r기본 더블형,f안붙어있으니
		D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));
		//z를 회전시켜야 xy평면이 돌아간다.

		//행렬은 교환법칙이 성립하지 않는다.
		//스*자*이*공*부
		//s *r * T * R * p
		//스케일 행렬 * 자전행렬(r - 스스로 돌아) *이동행렬 * 공전행렬 * 부모행렬

		//world = S *R* T;
		world = world * R;
	}

	

	//Create Constant Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		//cpu에서 써주고 gpu에서 읽어간다 해서 dynamic
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TRANSFORM_DATA);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		//subresource 매 프레임마다 
		auto hr = graphics->GetDevice()->CreateBuffer(&desc, nullptr, &gpu_buffer);
		assert(SUCCEEDED(hr));
	}

	//Create Rasterizer state
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		//IA, RS,OM stage 코딩불가 , 세팅만 하는것, 흘러간것 못바꿔
		desc.FillMode = D3D11_FILL_SOLID; //D3D11_FILL_WIREFRAME
		desc.CullMode = D3D11_CULL_BACK; //컬링을 어떻게 할것이냐
		desc.FrontCounterClockwise = false;

		//culling 카메라가 보이지 않는거 다 지운다.
		//cliping 그린후에 자른다. 비용이 발생 조금더.

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
	//cominterface 로 만들었으니 delete로 지우면 안돼 release 로해야돼
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
	world._42 = 100;*///위의 world다.

	//D3DZMATRIX - 행 우선 행렬
	//GPU - shader - matrix - 열 우선 행렬

	static float radian = 0.0f; //정적변수니 0.0으로 초기화 자동으로 된다.
	radian += 0.01f;
	D3DXMATRIX P;
	D3DXMatrixRotationZ(&P, radian);
	//부모행렬을 계속 따라간다. 자식들은 

	D3DXMatrixTranspose(&cpu_buffer.world, &world);
	//cpu_buffer.world = world;
	D3DXMatrixTranspose(&cpu_buffer.view, &view);
		//cpu_buffer.view = view;
	D3DXMatrixTranspose(&cpu_buffer.projection, &projection);
		//cpu_buffer.projection = projection;

	D3D11_MAPPED_SUBRESOURCE mapped_subresource; //중재자 
	graphics->GetDeviceContext()->Map
	(
		gpu_buffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mapped_subresource
	); //gpu하는것을 GETdevicecontext

	memcpy(mapped_subresource.pData, &cpu_buffer, sizeof(TRANSFORM_DATA));

	graphics->GetDeviceContext()->Unmap(gpu_buffer, 0);

}

void Execute::Rendor()
{
	uint stride = sizeof(vertexcolor); // 보폭// 정점
	uint offset = 0;//시작점 
	graphics->Begin();
	{
		//IA
		graphics->GetDeviceContext()->IAGetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout);
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //어떻게 찍을지 알려줌
		graphics->GetDeviceContext()->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
		//index Buffer는 IA에 들어간다. 어떤정점이 몇번쨰로 호출되는가 세팅
		//

		//VS// 정점 10개면 10번돈다. /GPU로 병렬처리
		graphics->GetDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);
		graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &gpu_buffer);

		//RS
		graphics->GetDeviceContext()->RSSetState(rasterizer_state);

		//PS , grapic 관련 CPU deviceContext
		graphics->GetDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);
		graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &shader_resource);
		//indexbuffer 있으면 drawIndexed로 바뀐다.
		//graphics->GetDeviceContext()->Draw(3, 0); //3점, 0부터 그리기(스타트지점)
		graphics->GetDeviceContext()->DrawIndexed(6,0, 0);
	}
	//앞으로 그릴것들은 비긴과 엔드 사이에만 넣으면 된다.
	//도화지 세팅, 프레젠트 하는것 신경쓸 필요 없다.
	graphics->End();
}

//		0

//0		0
//점인지 선인지 선을 이어서 안을 채우라는 이야기인지 
//이정보까지 써줘야한다.


