
struct PS_INPUT
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
};

cbuffer constant : register(b0)
{
	unsigned int _time;
}

float4 mainps(PS_INPUT input) : SV_TARGET
{
	return float4(input.color, 1.0f);
}