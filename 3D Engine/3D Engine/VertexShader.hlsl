struct VS_INPUT {
	float4 pos: POSITION;
	float3 col: COLOR;
};

struct VS_OUTPUT {
	float4 pos: SV_POSITION;
	float3 col: COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = input.pos;
	output.col = input.col;

	return output;
}