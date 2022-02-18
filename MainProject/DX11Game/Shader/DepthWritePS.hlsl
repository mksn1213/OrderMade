struct PS_IN
{
	float4	Pos			: SV_Position;
	float2	Tex			: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float3	PosForPS	: TEXCOORD2;
	float4  shadowPos	: TEXCOORD3;
};

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(1,0,0,1);
	color.r = pin.shadowPos.z / pin.shadowPos.w;
	return color;
}