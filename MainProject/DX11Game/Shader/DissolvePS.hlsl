/**
*
* @file		DissolvePS.hlsl
* @brief	ディゾルブ用ピクセルシェーダー
* @author	SHONOSUKE MAKITA
* @date		2022/02/03  実装開始
*
*/
// パラメータ
struct VS_OUTPUT
{
	float4	Position	: SV_Position;
	float2	TexCoord	: TEXCOORD0;
	float4	Diffuse		: COLOR0;
};

// グローバル
cbuffer Parameter : register(b0)
{
	float4 value;
}

Texture2D		baseTex		: register(t0);		// ベーステクスチャ
Texture2D		dissolveTex	: register(t1);		// ディゾルブテクスチャ
SamplerState	samp		: register(s0);		// サンプラ

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = float4(1,1,1,1);
	color = baseTex.Sample(samp, input.TexCoord);

	// ディゾルブ
	float dissolve = dissolveTex.Sample(samp, input.TexCoord).r;
	color.a = step(dissolve, value.x);

	return color;
}