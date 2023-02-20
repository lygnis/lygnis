
Texture2D Texture : register(t0);
SamplerState TextureSampler: register(s0);



struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};

cbuffer constant : register(b0)
{
	row_major float4x4 _world;
	row_major float4x4 _view;
	row_major float4x4 _proj;
	float4 _light_dir;
	float4 _cameraPos;
	float _discard;
};

float4 mainps(PS_INPUT input) : SV_TARGET
{
	//float4 final_color = Texture.Sample(TextureSampler,input.texcoord);
	//if (final_color.r < 0.1 && final_color.g < 0.1)
		return float4(1, 1, 1, 1);

	//return Texture.Sample(TextureSampler,input.texcoord);
}

