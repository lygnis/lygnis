
Texture2D Texture : register(t0);
SamplerState TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal: NORMAL;
	float3 direction_cam: TEXCOORD1;
};

cbuffer constant : register(b0)
{
	row_major float4x4 _world;
	row_major float4x4 _view;
	row_major float4x4 _proj;
	float4 _light_dir;
};

float4 mainps(PS_INPUT input) : SV_TARGET
{
	// ambient_light
	float ka = 0.1f;
	// 하얀색으로 초기화
	float3 ia = float3(1.0f, 1.0f, 1.0f);
	float3 ambient_light = ka * ia;


	 //Diffuse light (난반사)
	float kd = 0.7f;
	float3 id = float3(1.0f, 1.0f, 1.0f);
	// 법선벡터와 빛의 내적
	float amount_diffuse_light =max(0.0, dot(_light_dir.xyz, input.normal));

	float3 diffuse_light = kd * amount_diffuse_light * id;

	//// specular light (정반사)
	float ks = 1.0f;
	float3 is = float3(1.0, 1.0, 1.0);
	float3 reflected_light = reflect(_light_dir.xyz, input.normal);
	float shininess = 100.0;
	float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_cam)), shininess);

	float3 specular_light = ks * amount_specular_light * is;

	float3 final_light = ambient_light + diffuse_light + specular_light;

	return float4(final_light, 1.0f);
}
