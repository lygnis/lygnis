// ���� ���̴� �Է� ������
struct VS_INPUT
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
	float4 color : COLOR;
};

// �ȼ� ���̴��� ���� ������
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};
cbuffer constant : register(b0)
{
	float3 position;
	float2 texcoord;
}

VS_OUTPUT mainvs(VS_INPUT  input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = float4(position, 1.0);
	output.color = input.color;
	output.texcoord = texcoord;

	return output;
}