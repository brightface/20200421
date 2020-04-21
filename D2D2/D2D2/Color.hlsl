struct VertexInput
{					//Semantic : �������� ��ó�� ���ҿ� ���� �и��� �ǹ̸� �ο��ϱ� ���� Ű����, �ںκ��� semantic index
	float4 position : POSITION0;
	float4 color : COLOR0;

};
struct PixelInput
{
	float4 position : SV_POSITION0; //SV = system_value; / �߿��� �����̴�.
	float4 color : COLOR0; 
};

cbuffer TransforBuffer : register(b0) //0~13// slot buffer// 4096 * 16byte
{
    //row_major matrix
     matrix world;
     matrix view;
     matrix proj;
};
PixelInput VS(VertexInput input)
{
    //1,2,3,1 * 0000
    //          0000
    //          0000
    //          0000
	PixelInput output;
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj); //proj �� cliping space �� ���ԵǾ��ִ�.
	output.color = input.color;
	
	return output;
}

float4 PS(PixelInput input) : SV_Target
{
	return input.color;
}