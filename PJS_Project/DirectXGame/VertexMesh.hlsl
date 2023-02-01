// 정점 쉐이더 입력 데이터
struct VS_INPUT
{
	float4 position: POSITION;
	float2 texcoord: TEXCOORD;
	float3 normal: NORMAL;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

VS_OUTPUT mainvs(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	return output;
}