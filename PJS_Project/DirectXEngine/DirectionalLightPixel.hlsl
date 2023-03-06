Texture2D Color : register(t0);
SamplerState ColorSampler: register(s0);


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
	float4 _cameraPos;

	float4 _light_position;
	float _light_radius;
	float _time;
};

float4 mainps(PS_INPUT input) : SV_TARGET
{
	// �ؽ�ó���� �ȼ��� ��´�
	// �Ű������� ���÷�, �� ǥ�鿡 ���� ������ ǥ���ϱ� ���� �ؽ�Ʈ ��ǥ
	float4 color = Color.Sample(ColorSampler, float2(input.texcoord.x , 1.0 - input.texcoord.y));
	
	// ambient_light
	float ka = 8.5f;
	// �Ͼ������ �ʱ�ȭ
	float3 ia = float3(0.09f, 0.082f, 0.082f);
	ia *= (color.rgb);


	float3 ambient_light = ka * ia;


	//Diffuse light (���ݻ�)
   float kd = 0.7f;
  
   float amount_diffuse_light = dot(_light_dir.xyz, input.normal);
   // ������ ������ -1 ~1 �� �����Ѵ�
   float3 id = float3(1, 1, 1);
   id *= (color.rgb);
   // amoint light�� id �� ����ϴµ� ����ϱ� ������ ���� ������� �����Ѵ�
   float3 diffuse_light = kd * id * amount_diffuse_light;

   //// specular light (���ݻ�)
   float ks = 0.0;
   float3 is = float3(1.0, 1.0, 1.0);
   float3 reflected_light = reflect(_light_dir.xyz, input.normal);
   float shininess = 20.0;
   float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_cam)), shininess);

   float3 specular_light = ks * amount_specular_light * is;

   float3 final_light = ambient_light + diffuse_light + specular_light;

   return float4(final_light, 1.0f);
}