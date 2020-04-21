struct VertexInput
{					//Semantic : 데이터의 출처나 역할에 대한 분명한 의미를 부여하기 위한 키워드, 뒤부분이 semantic index
	float4 position : POSITION0;
	float4 color : COLOR0;

};
struct PixelInput
{
	float4 position : SV_POSITION0; //SV = system_value; / 중요한 정보이다.
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
    output.position = mul(output.position, proj); //proj 는 cliping space 가 포함되어있다.
	output.color = input.color;
	
	return output;
}

float4 PS(PixelInput input) : SV_Target
{
	return input.color;
}