/**
*
* @file		DissolvePS.hlsl
* @brief	�f�B�]���u�p�s�N�Z���V�F�[�_�[
* @author	SHONOSUKE MAKITA
* @date		2022/02/03  �����J�n
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

Texture2D		baseTex		: register(t0);		// �x�[�X�e�N�X�`��
Texture2D		dissolveTex	: register(t1);		// �f�B�]���u�e�N�X�`��
SamplerState	samp		: register(s0);		// �T���v��

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = float4(1,1,1,1);
	color = baseTex.Sample(samp, input.TexCoord);

	// �f�B�]���u
	float dissolve = dissolveTex.Sample(samp, input.TexCoord).r;
	color.a = step(dissolve, value.x);

	return color;
}