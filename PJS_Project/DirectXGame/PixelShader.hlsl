
Texture2D Texture : register(t0);
SamplerState TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

cbuffer constant : register(b0)
{
	row_major float4x4 _world;
	row_major float4x4 _view;
	row_major float4x4 _proj;
	unsigned int _time;
}

float4 mainps(PS_INPUT input) : SV_TARGET
{
	return Texture.Sample(TextureSampler, input.texcoord*0.5f );
}