#pragma once
//랜더링 데이터를 넣고 그리는 코드 다 집어넣을것이다.
//이안에 그래픽스가 다 있어야한다.
//Rendoring pipeline
//-IA -VS- RS - PS - OM

//IA: INPUT assembler stage : 기본데이터를 넣어주면 가공되서 출력이된다.
//볏집이 기본데이터 , 정점이 기본데이터 - vertex

struct vertexcolor
{
	D3DXVECTOR3 position;//x,y,z
	D3DXCOLOR color;
};//위치정보 ,vertex data를 만들어줘야한다.

struct vertexTexture
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv; //tesccord x,y
};
struct TRANSFORM_DATA
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};
//class Graphics;//이렇게 써도 상관이 없다. 
class Execute final
{
public:
	Execute();
	~Execute();

	void Update();
	void Rendor();
private:
	class Graphics* graphics = nullptr;
	//5번줄과 같다. 근데 줄 짧게하려고
	//자료형 앞 CLASS키워드는 class상단의 전방선언과 동일하다.

	//vertexcolor* vertices = nullptr;
	vertexTexture* vertices = nullptr;
	ID3D11Buffer* vertex_buffer = nullptr;

	uint* indices = nullptr; //이데이터 바로 gpu pipeline 못들어가 그래서 바꿔준다.
	ID3D11Buffer* index_buffer = nullptr;

	ID3D11InputLayout* input_layout = nullptr; //레이아웃을 알려주는 정보
	
	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr; //2진파일 빠르게 저장하는 포인터 , 블롭이란 데이터

	ID3D11PixelShader* pixel_shader = nullptr;
	ID3D10Blob* ps_blob = nullptr;

	//4 by 4 행렬을 쓴다. 동차좌표를 쓴다.
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	/*
		1 0 0 0 동차가 0이면 방향벡터 x축방향의 크기 1을 가진 벡터
		0 1 0 0 동차가 0이니 y축방향의 방향벡터
		0 0 1 0 
		0 0 0 1
	*/
	//공간이 커지면 그안에 데이터도 같이 커진다. 공간만 잘 만지면 행렬을 통해서 변환가능
	TRANSFORM_DATA cpu_buffer;
	ID3D11Buffer* gpu_buffer = nullptr; // 정확히 constanct buffer

	ID3D11RasterizerState* rasterizer_state = nullptr;
	ID3D11ShaderResourceView* shader_resource;
	

	//testure
	//ID3D11Texture2D
	//RTV : OM STAGE
	//DSV : OM STAGE
	//SRV 
	//UAV
};

//Rendering Pipiline
// IA - VS - RS - PS - OM
//IA,RS,OM : 코드를 수정할수가 없다.
//VS, RS : 코드를 수정가능
//IA : Input Assembler stage

// VS : Vertex Shader
//Shader : GPU를 동작시키는 함수들의 집합
//assembler 로 만들어졌다. 
//HLSL로 만들언것 shader 보완하고자 HLSL : 고수준의 쉐이더 언어 ,GLSL(openGL) 
//VS
// Transform , 공간변환 한다. 0~1 정규화를 시킨다. 보이지 않는부분은 그리지 않는다.
//앞면인가 뒷면인가 판단해서 그리지 않는다.
//RS : 정규화된 공간을 다시 늘려준다. Resterizer stage 
//~NDC(nomalize 어찌고 저찌고) 좌표계로 찍었다. 9강 끝

//Local : 지역좌표계 , 설계도 
//이미 우리가 만들었다.

//world : 세계로 들어왔을때, 세계좌표계
//view : 보여지는 영역 , 시야공간, 내눈을 기준으로 시야에 위치 하는 공간
//이걸로 변환을 한다.

//projection : 투영공간, 3D->2D로 변형시키는 공간, 차원을 낮추는 공간
//clip-Homogenous space 동차공간 : 오리다. 내 view공간에 들어오는것과 안들어오는것 ,위에서 만들어진 공간 정규화하는 공간
//------------------------------------------------ vs가 여기까지 담당

//RS <RASTERIZE STATE> 
//Clippling 오리기
//Back-face culling
//Scan Transform
//NDC - Euclidean space 유클리드 공간
//viewport transform- 공간을 다시 원래대로 늘려준다.

//동차공간 : 하나를 더 만들어 쓰는것 
//{1, 0, 0, w<방향인지 위치인지>} 동차계산시 w를 1로 맞추고 한다.
//w -> 0 방향, w-> 1 위치

