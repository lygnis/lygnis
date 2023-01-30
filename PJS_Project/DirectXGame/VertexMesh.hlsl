// 정점 쉐이더 입력 데이터
struct VS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD;
};
// 픽셀 쉐이더로 보낼 데이터
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};


VS_OUTPUT mainvs(VS_INPUT  input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	return output;
}