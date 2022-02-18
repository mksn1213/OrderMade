#define MAX_BONE_MATRIX	64

// �s��
cbuffer Matrix : register(b1)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
}

// �{�[���̃|�[�Y�s��
cbuffer global_bones : register(b2) {
	matrix g_BoneWorld[MAX_BONE_MATRIX];
};

// �p�����[�^
struct VS_INPUT {
	float3	Pos		: POSITION;
	float3	Normal	: NORMAL;
	float2	Tex		: TEXCOORD0;
	uint4	Bone	: BONE_INDEX;	// �{�[���̃C���f�b�N�X
	float4	Weight	: BONE_WEIGHT;	// �{�[���̏d��
};

struct VS_OUTPUT {
	float4	Pos			: SV_Position;
	float2	Tex			: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float3	PosForPS	: TEXCOORD2;
	float4  shadowPos	: TEXCOORD3;
};

// �X�L�j���O��̒��_�E�@��
struct SKIN {
	float4 Pos;
	float3 Norm;
};

// ���_���X�L�j���O (�{�[���ɂ��ړ�)
SKIN SkinVert(VS_INPUT input)
{
	SKIN output;
	float4 Pos = float4(input.Pos, 1.0f);
	float3 Norm = input.Normal;
	if (input.Weight.x == 0.0f)
	{
		// �{�[������
		output.Pos = Pos;
		output.Norm = Norm;
	}
	else
	{
		// �{�[��0
		uint uBone = input.Bone.x;
		float fWeight = input.Weight.x;
		matrix m = g_BoneWorld[uBone];
		output.Pos = fWeight * mul(Pos, m);
		output.Norm = fWeight * mul(Norm, (float3x3)m);
		// �{�[��1
		uBone = input.Bone.y;
		fWeight = input.Weight.y;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
		// �{�[��2
		uBone = input.Bone.z;
		fWeight = input.Weight.z;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
		// �{�[��3
		uBone = input.Bone.w;
		fWeight = input.Weight.w;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
	}
	return output;
}

//
// ���_�V�F�[�_
//
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	SKIN vSkinned = SkinVert(input);
	output.Pos = mul(vSkinned.Pos, world);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, proj);
	output.shadowPos = output.Pos;
	return output;
}