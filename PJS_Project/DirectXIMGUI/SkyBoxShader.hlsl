Texture2D Texture : register(t0);
SamplerState TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
	float3 normal: NORMAL;
	float4 color : COLOR;
	float3 direction_cam: TEXCOORD1;
	float _discard : TEXCOORD2;
};

float4 mainps(PS_INPUT input) : SV_TARGET
{
	return Texture.Sample(TextureSampler, 1.0 - input.texcoord);
}

float4 ps_testing(PS_INPUT input) : SV_TARGET
{
	float4 color = Texture.Sample(TextureSampler, 1.0 - input.texcoord);// *input.c;
	if (color.a < 0.5)        discard;
	return color;
}