/**
*
* @file		MultiTexturePS.hlsl
* @brief	マルチテクスチャ用+ディゾルブ用ピクセルシェーダー
* @author	SHONOSUKE MAKITA
* @date		2022/02/05  実装開始
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

Texture2D		baseTex		: register(t0);	// ベーステクスチャ
Texture2D		dissolveTex	: register(t1);	// ディゾルブテクスチャ
Texture2D		multiTex	: register(t2);	// 張り合わせるテクスチャ
Texture2D		multiTex2	: register(t3);	// 張り合わせるテクスチャ
SamplerState	samp		: register(s0);	// サンプラ

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = input.Diffuse;
	color *= baseTex.Sample(samp, input.TexCoord);

	// テクスチャの重ね合わせ
	float4 blendColor = multiTex.Sample(samp, input.TexCoord);
	color.rgb = color.rgb * (1.0f - blendColor.a) + blendColor.rgb * blendColor.a;
	float4 blendColor2 = multiTex2.Sample(samp, input.TexCoord);
	color.rgb = color.rgb * (1.0f - blendColor2.a) + blendColor2.rgb * blendColor2.a;

	// ディゾルブ
	float dissolve = dissolveTex.Sample(samp, input.TexCoord).r;
	// 透明部分は省く
	if (color.a > 0)	color.a = step(dissolve, value.x);

	return color;
}