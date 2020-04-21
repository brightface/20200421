#pragma once
//������ �����͸� �ְ� �׸��� �ڵ� �� ����������̴�.
//�̾ȿ� �׷��Ƚ��� �� �־���Ѵ�.
//Rendoring pipeline
//-IA -VS- RS - PS - OM

//IA: INPUT assembler stage : �⺻�����͸� �־��ָ� �����Ǽ� ����̵ȴ�.
//������ �⺻������ , ������ �⺻������ - vertex

struct vertexcolor
{
	D3DXVECTOR3 position;//x,y,z
	D3DXCOLOR color;
};//��ġ���� ,vertex data�� ���������Ѵ�.

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
//class Graphics;//�̷��� �ᵵ ����� ����. 
class Execute final
{
public:
	Execute();
	~Execute();

	void Update();
	void Rendor();
private:
	class Graphics* graphics = nullptr;
	//5���ٰ� ����. �ٵ� �� ª���Ϸ���
	//�ڷ��� �� CLASSŰ����� class����� ���漱��� �����ϴ�.

	//vertexcolor* vertices = nullptr;
	vertexTexture* vertices = nullptr;
	ID3D11Buffer* vertex_buffer = nullptr;

	uint* indices = nullptr; //�̵����� �ٷ� gpu pipeline ���� �׷��� �ٲ��ش�.
	ID3D11Buffer* index_buffer = nullptr;

	ID3D11InputLayout* input_layout = nullptr; //���̾ƿ��� �˷��ִ� ����
	
	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr; //2������ ������ �����ϴ� ������ , ����̶� ������

	ID3D11PixelShader* pixel_shader = nullptr;
	ID3D10Blob* ps_blob = nullptr;

	//4 by 4 ����� ����. ������ǥ�� ����.
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	/*
		1 0 0 0 ������ 0�̸� ���⺤�� x������� ũ�� 1�� ���� ����
		0 1 0 0 ������ 0�̴� y������� ���⺤��
		0 0 1 0 
		0 0 0 1
	*/
	//������ Ŀ���� �׾ȿ� �����͵� ���� Ŀ����. ������ �� ������ ����� ���ؼ� ��ȯ����
	TRANSFORM_DATA cpu_buffer;
	ID3D11Buffer* gpu_buffer = nullptr; // ��Ȯ�� constanct buffer

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
//IA,RS,OM : �ڵ带 �����Ҽ��� ����.
//VS, RS : �ڵ带 ��������
//IA : Input Assembler stage

// VS : Vertex Shader
//Shader : GPU�� ���۽�Ű�� �Լ����� ����
//assembler �� ���������. 
//HLSL�� ������ shader �����ϰ��� HLSL : ������� ���̴� ��� ,GLSL(openGL) 
//VS
// Transform , ������ȯ �Ѵ�. 0~1 ����ȭ�� ��Ų��. ������ �ʴºκ��� �׸��� �ʴ´�.
//�ո��ΰ� �޸��ΰ� �Ǵ��ؼ� �׸��� �ʴ´�.
//RS : ����ȭ�� ������ �ٽ� �÷��ش�. Resterizer stage 
//~NDC(nomalize ����� �����) ��ǥ��� �����. 9�� ��

//Local : ������ǥ�� , ���赵 
//�̹� �츮�� �������.

//world : ����� ��������, ������ǥ��
//view : �������� ���� , �þ߰���, ������ �������� �þ߿� ��ġ �ϴ� ����
//�̰ɷ� ��ȯ�� �Ѵ�.

//projection : ��������, 3D->2D�� ������Ű�� ����, ������ ���ߴ� ����
//clip-Homogenous space �������� : ������. �� view������ �����°Ͱ� �ȵ����°� ,������ ������� ���� ����ȭ�ϴ� ����
//------------------------------------------------ vs�� ������� ���

//RS <RASTERIZE STATE> 
//Clippling ������
//Back-face culling
//Scan Transform
//NDC - Euclidean space ��Ŭ���� ����
//viewport transform- ������ �ٽ� ������� �÷��ش�.

//�������� : �ϳ��� �� ����� ���°� 
//{1, 0, 0, w<�������� ��ġ����>} �������� w�� 1�� ���߰� �Ѵ�.
//w -> 0 ����, w-> 1 ��ġ

