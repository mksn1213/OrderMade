// 2D用頂点シェーダ

// グローバル
cbuffer global : register(b0) 
{
	matrix g_mWorld;
	matrix g_mView;
	matrix g_mProjection;
	matrix g_mTexture;
};

// パラメータ
struct VS_INPUT 
{
	float3	Position	: POSITION;
	float4	Diffuse		: COLOR;
	float2	TexCoord	: TEXCOORD;
};

struct VS_OUTPUT 
{
	float4	Position	: SV_Position;
	float2	TexCoord	: TEXCOORD;
	float4	Diffuse		: COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 P = mul(float4(input.Position, 1.0f), g_mWorld);
	P = mul(P, g_mView);
	output.Position = mul(P, g_mProjection);
	output.TexCoord = mul(float4(input.TexCoord, 0.0f, 1.0f), g_mTexture).xy;
	output.Diffuse = input.Diffuse;
	return output;
}
