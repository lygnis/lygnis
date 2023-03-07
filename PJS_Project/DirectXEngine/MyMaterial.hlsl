struct VS_INPUT
{
	float4 position: POSITION;
	float2 texcoord: TEXCOORD;
	float3 normal: NORMAL;
	float3 tangent: TANGENT;
	float3 binormal: BINORMAL;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};


cbuffer constant: register(b0)
{
	row_major float4x4 world;
	row_major float4x4 view;
	row_major float4x4 proj;
};



VS_OUTPUT mainvs(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//WORLD SPACE
	output.position = mul(input.position, world);
	//VIEW SPACE
	output.position = mul(output.position, view);
	//SCREEN SPACE
	output.position = mul(output.position, proj);

	output.texcoord = input.texcoord;

	// ³ë¸»¸ÊÇÎ
	//output.tbn[0] = normalize(mul(input.tangent, world));
	//output.tbn[1] = normalize(mul(input.binormal,world));
	//output.tbn[2] = normalize(mul(input.normal, world));

	return output;
}



struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

Texture2D Color : register(t0);
SamplerState ColorSampler: register(s0);

float4 mainps(PS_INPUT input) : SV_TARGET
{

	return Color.Sample(ColorSampler, input.texcoord);
}