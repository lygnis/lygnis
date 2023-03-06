Texture2D Texture : register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal: NORMAL;
	float3 direction_cam: TEXCOORD1;
};



float4 mainps(PS_INPUT input) : SV_TARGET
{

	return Texture.Sample(TextureSampler, 1.0 - input.texcoord);
}