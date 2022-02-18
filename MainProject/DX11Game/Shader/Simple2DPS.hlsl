// 2D�p�s�N�Z���V�F�[�_

// �p�����[�^
struct VS_OUTPUT 
{
	float4	Position	: SV_Position;
	float2	TexCoord	: TEXCOORD;
	float4	Diffuse		: COLOR;
};

Texture2D		baseTex		: register(t0);		// �x�[�X�e�N�X�`��
SamplerState	samp		: register(s0);		// �T���v��

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = input.Diffuse;
	color *= baseTex.Sample(samp, input.TexCoord);
	return color;
}
