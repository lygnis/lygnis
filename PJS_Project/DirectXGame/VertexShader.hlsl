// Á¤Á¡ ½¦ÀÌ´õ ÀÔ·Â µ¥ÀÌÅÍ
struct VS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD;
};
// ÇÈ¼¿ ½¦ÀÌ´õ·Î º¸³¾ µ¥ÀÌÅÍ
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

cbuffer constant : register(b0)
{
	row_major float4x4 _world;
	row_major float4x4 _view;
	row_major float4x4 _proj;
	unsigned int _time;
}

VS_OUTPUT mainvs(VS_INPUT  input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	//output.position = lerp(input.position, input.position1, sin(_time/1000.0f)+1.0f / 2.0f);
	
	// ¿ùµå ÁÂÇ¥°è
	output.position = mul(input.position, _world);
	// ºä ÁÂÇ¥°è
	output.position = mul(output.position, _view);
	// Åõ¿µ ÁÂÇ¥°è
	output.position = mul(output.position, _proj);

	output.texcoord = input.texcoord;
	//output.color = input.color;

	return output;
}