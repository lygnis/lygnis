// ���� ���̴� �Է� ������
struct VS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
};
// �ȼ� ���̴��� ���� ������
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
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
}

VS_OUTPUT mainvs(VS_INPUT  input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	//output.position = lerp(input.position, input.position1, sin(_time/1000.0f)+1.0f / 2.0f);

	// ���� ��ǥ��
	output.position = mul(input.position, _world);
	output.world_pos = output.position.xyz;
	// �� ��ǥ��
	output.position = mul(output.position, _view);
	// ���� ��ǥ��
	output.position = mul(output.position, _proj);

	output.texcoord = input.texcoord;
	output.normal = input.normal;
	//output.color = input.color;

	return output;
}
