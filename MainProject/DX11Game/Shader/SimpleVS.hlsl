// 頂点シェーダ

// グローバル
cbuffer global : register(b0)
{
	matrix g_mtxWorld;
	matrix g_mtxView;
	matrix g_mtxProj;
	matrix g_mTexture;
};

cbuffer ShadowViewProj : register(b1)
{
	float4x4 shadowVPS;
}

// パラメータ
struct VS_INPUT {
	float3	Position	: POSITION;
	float3	Normal		: NORMAL;
	float4	Diffuse		: COLOR0;
	float2	TexCoord	: TEXCOORD0;
};

struct VS_OUTPUT {
	float4	Position	: SV_Position;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Diffuse		: COLOR0;
	float4  ShadowUV	: TEXCOORD3;
	float2  UV			: TEXCOORD4;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 Pos = float4(input.Position, 1.0f);
	output.Position = mul(Pos, g_mtxWorld);
	// ワールド行列計算後、ライト空間の行列をかける
	output.ShadowUV = mul(output.Position, shadowVPS);
	// 画面へ出力するためのカメラ行列をかける
	output.Position = mul(output.Position, g_mtxView);
	output.Position = mul(output.Position, g_mtxProj);

	output.Pos4PS = mul(Pos, g_mtxWorld).xyz;
	output.Normal = mul(float4(input.Normal, 0.0f), g_mtxWorld).xyz;
	output.TexCoord = mul(float4(input.TexCoord, 0.0f, 1.0f), g_mTexture).xy;
	output.Diffuse = input.Diffuse;
	return output;
}
