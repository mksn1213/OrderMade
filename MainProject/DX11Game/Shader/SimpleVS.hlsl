// ���_�V�F�[�_

// �O���[�o��
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

// �p�����[�^
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
	// ���[���h�s��v�Z��A���C�g��Ԃ̍s���������
	output.ShadowUV = mul(output.Position, shadowVPS);
	// ��ʂ֏o�͂��邽�߂̃J�����s���������
	output.Position = mul(output.Position, g_mtxView);
	output.Position = mul(output.Position, g_mtxProj);

	output.Pos4PS = mul(Pos, g_mtxWorld).xyz;
	output.Normal = mul(float4(input.Normal, 0.0f), g_mtxWorld).xyz;
	output.TexCoord = mul(float4(input.TexCoord, 0.0f, 1.0f), g_mTexture).xy;
	output.Diffuse = input.Diffuse;
	return output;
}
