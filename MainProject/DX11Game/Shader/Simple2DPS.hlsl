// 2D用ピクセルシェーダ

// パラメータ
struct VS_OUTPUT 
{
	float4	Position	: SV_Position;
	float2	TexCoord	: TEXCOORD;
	float4	Diffuse		: COLOR;
};

Texture2D		baseTex		: register(t0);		// ベーステクスチャ
SamplerState	samp		: register(s0);		// サンプラ

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = input.Diffuse;
	color *= baseTex.Sample(samp, input.TexCoord);
	return color;
}
