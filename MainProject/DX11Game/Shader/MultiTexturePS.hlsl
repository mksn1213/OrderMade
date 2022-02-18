/**
*
* @file		MultiTexturePS.hlsl
* @brief	�}���`�e�N�X�`���p+�f�B�]���u�p�s�N�Z���V�F�[�_�[
* @author	SHONOSUKE MAKITA
* @date		2022/02/05  �����J�n
*
*/

// �p�����[�^
struct VS_OUTPUT
{
	float4	Position	: SV_Position;
	float2	TexCoord	: TEXCOORD0;
	float4	Diffuse		: COLOR0;
};

// �O���[�o��
cbuffer Parameter : register(b0)
{
	float4 value;
}

Texture2D		baseTex		: register(t0);	// �x�[�X�e�N�X�`��
Texture2D		dissolveTex	: register(t1);	// �f�B�]���u�e�N�X�`��
Texture2D		multiTex	: register(t2);	// ���荇�킹��e�N�X�`��
Texture2D		multiTex2	: register(t3);	// ���荇�킹��e�N�X�`��
SamplerState	samp		: register(s0);	// �T���v��

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = input.Diffuse;
	color *= baseTex.Sample(samp, input.TexCoord);

	// �e�N�X�`���̏d�ˍ��킹
	float4 blendColor = multiTex.Sample(samp, input.TexCoord);
	color.rgb = color.rgb * (1.0f - blendColor.a) + blendColor.rgb * blendColor.a;
	float4 blendColor2 = multiTex2.Sample(samp, input.TexCoord);
	color.rgb = color.rgb * (1.0f - blendColor2.a) + blendColor2.rgb * blendColor2.a;

	// �f�B�]���u
	float dissolve = dissolveTex.Sample(samp, input.TexCoord).r;
	// ���������͏Ȃ�
	if (color.a > 0)	color.a = step(dissolve, value.x);

	return color;
}