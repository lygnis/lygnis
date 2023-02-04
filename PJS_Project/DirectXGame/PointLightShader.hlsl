
Texture2D TextureColor : register(t0);
SamplerState TextureColorSampler: register(s0);



struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal: NORMAL;
	float3 world_pos: TEXCOORD1;
};

cbuffer constant : register(b0)
{
	row_major float4x4 _world;
	row_major float4x4 _view;
	row_major float4x4 _proj;
	float4 _light_dir;
	float4 _cameraPos;

	float4 _light_position;
	float _light_radius;
	float _time;
};

float4 mainps(PS_INPUT input) : SV_TARGET
{
	// 텍스처에서 픽셀을 얻는다
	// 매개변수는 샘플러, 구 표면에 지구 지도를 표시하기 위한 텍스트 좌표
	float4 tex_color = TextureColor.Sample(TextureColorSampler, (1.0 - input.texcoord));
	float ka = 1.5;
	float3 ia = float3(0.09, 0.082, 0.082);
	ia *= (tex_color.rgb);


	float3 ambient_light = ka * ia;


	//Diffuse light (난반사)
   float kd = 0.7f;
   float3 light_dir = normalize(_light_position.xyz - input.world_pos.xyz);
   float distance_light_object = length(_light_position.xyz - input.world_pos.xyz);

   float fade_area = max(0, distance_light_object - _light_radius);

   float constant_func = 1.0;
   float linear_func = 1.0;
   float quadratic_func = 1.0;

   float attenuation = constant_func + linear_func* fade_area + linear_func* fade_area + quadratic_func* fade_area* fade_area;

   // 법선벡터와 빛의 내적
   // 양수 값으로 제한
   float amount_diffuse_light = max(0, dot(light_dir.xyz, input.normal));
   // 조명의 범위는 -1 ~1 로 설정한다
   float3 id = float3(1, 1, 1);
   id *= (tex_color.rgb);
   // amoint light는 id 를 계산하는데 사용하기 때문에 최종 결과에서 제거한다
   float3 diffuse_light = (kd * id * amount_diffuse_light)/ attenuation;

   //// specular light (정반사)
   float ks = 1.0;
   float3 direction_cam = normalize(input.world_pos.xyz - _cameraPos.xyz);

   float3 is = float3(1.0, 1.0, 1.0);
   float3 reflected_light = reflect(light_dir.xyz, input.normal);
   float shininess = 30.0;
   float amount_specular_light = pow(max(0.0, dot(reflected_light, direction_cam)), shininess);

   float3 specular_light = (ks * amount_specular_light * is) / attenuation;


   float3 final_light = ambient_light + diffuse_light + specular_light;

   return float4(final_light, 1.0f);
}
