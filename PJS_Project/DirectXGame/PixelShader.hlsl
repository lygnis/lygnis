
Texture2D EarthColor : register(t0);
SamplerState EarthColorSampler: register(s0);

Texture2D EarthSpecular : register(t1);
SamplerState EarthSpecularSampler: register(s1);

Texture2D Clouds : register(t2);
SamplerState CloudsSampler: register(s2);

Texture2D EarthNight : register(t3);
SamplerState EarthNightSampler: register(s3);

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
	float _time;
};

float4 mainps(PS_INPUT input) : SV_TARGET
{
	// �ؽ�ó���� �ȼ��� ��´�
	// �Ű������� ���÷�, �� ǥ�鿡 ���� ������ ǥ���ϱ� ���� �ؽ�Ʈ ��ǥ
	float4 earth_color = EarthColor.Sample(EarthColorSampler, 1.0 - input.texcoord);
	// ������ ä�� �˻� ä�� ������ ����� �Ѵ�
	float earth_spec = EarthSpecular.Sample(EarthSpecularSampler, 1.0 - input.texcoord).r;
	// �������� �ݻ簡 �ȵǰ� �ؾ��Ѵ�
	float clouds = Clouds.Sample(CloudsSampler, 1.0 - input.texcoord + float2(_time/100.0,0)).r;
	// �㿡 Ȱ��ȭ �ؽ��� �۾�
	float4 night_color = EarthNight.Sample(EarthNightSampler, 1.0 - input.texcoord);

	// ambient_light
	float ka = 1.5f;
	// �Ͼ������ �ʱ�ȭ
	float3 ia = float3(0.09f, 0.082f, 0.082f);
	// ���� ���� ia ���Ѵ�.������ �ȼ��� ��´� ������ �ȼ��� ��´�.
	ia *= (earth_color.rgb );


	float3 ambient_light = ka * ia;


	 //Diffuse light (���ݻ�)
	float kd = 0.7f;
	float3 id_day = float3(1.0f, 1.0f, 1.0f);
	id_day *= (earth_color.rgb + clouds);

	// ������ ������ �ؽ�ó�� �ȼ� �������� �����Ѵ�.
	float3 id_night = float3(1.0f, 1.0f, 1.0f);
	id_night *= (night_color.rgb + clouds *0.3);
	// �������Ϳ� ���� ����
	float amount_diffuse_light = dot(_light_dir.xyz, input.normal);
	// ������ ������ -1 ~1 �� �����Ѵ�
	float3 id = lerp(id_night, id_day, (amount_diffuse_light + 1.0)/2.0);

	// amoint light�� id �� ����ϴµ� ����ϱ� ������ ���� ������� �����Ѵ�
	float3 diffuse_light = kd *  id;

	//// specular light (���ݻ�)
	float ks = earth_spec;
	float3 is = float3(1.0, 1.0, 1.0);
	float3 reflected_light = reflect(_light_dir.xyz, input.normal);
	float shininess = 20.0;
	float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_cam)), shininess);

	float3 specular_light = ks * amount_specular_light * is;

	float3 final_light = ambient_light + diffuse_light + specular_light;

	return float4(final_light, 1.0f);
}
