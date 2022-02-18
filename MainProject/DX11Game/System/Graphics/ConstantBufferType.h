#pragma once
#include <System/Defines.h>

struct SHADER_GLOBAL 
{
	XMMATRIX	mWorld;			// ���[���h�s��(�]�u�s��)
	XMMATRIX	mView;
	XMMATRIX	mProj;
	XMMATRIX	mTex;		// �e�N�X�`���s��(�]�u�s��)
	XMVECTOR	vEye;		// ���_���W
	XMVECTOR	vLightDir;	// ��������
	XMVECTOR	vLa;		// �����F(�A���r�G���g)
	XMVECTOR	vLd;		// �����F(�f�B�t���[�Y)
	XMVECTOR	vLs;		// �����F(�X�y�L����)
};

// �}�e���A�� (�V�F�[�_�p)
struct SHADER_MATERIAL 
{
	XMVECTOR	vAmbient;	// �A���r�G���g�F
	XMVECTOR	vDiffuse;	// �f�B�t���[�Y�F
	XMVECTOR	vSpecular;	// �X�y�L�����F
	XMVECTOR	vEmissive;	// �G�~�b�V�u�F
	XMVECTOR	vFlags;		// �e�N�X�`���L��
};

// �V�F�[�_�ɓn���{�[���s��z��
struct SHADER_BONE 
{
	XMMATRIX mBone[64];
	SHADER_BONE()
	{
		for (int i = 0; i < 64; i++) {
			mBone[i] = XMMatrixIdentity();
		}
	}
};

struct SHADER_GLOBAL_MESH
{
	XMMATRIX	mWorld;		// ���[���h�s��(�]�u�s��)
	XMMATRIX	mView;
	XMMATRIX	mProj;
	XMMATRIX	mTex;		// �e�N�X�`���s��(�]�u�s��)
};
struct SHADER_GLOBAL2_MESH
{
	XMVECTOR	vEye;		// ���_���W
	// ����
	XMVECTOR	vLightDir;	// ��������
	XMVECTOR	vLa;		// �����F(�A���r�G���g)
	XMVECTOR	vLd;		// �����F(�f�B�t���[�Y)
	XMVECTOR	vLs;		// �����F(�X�y�L����)
	// �}�e���A��
	XMVECTOR	vAmbient;	// �A���r�G���g�F(+�e�N�X�`���L��)
	XMVECTOR	vDiffuse;	// �f�B�t���[�Y�F
	XMVECTOR	vSpecular;	// �X�y�L�����F(+�X�y�L�������x)
	XMVECTOR	vEmissive;	// �G�~�b�V�u�F
};

struct SHADER_GLOBAL_POLYGON
{
	XMMATRIX	mWorld;		// ���[���h�ϊ��s��(�]�u�s��)
	XMMATRIX	mView;		// �r���[�ϊ��s��(�]�u�s��)
	XMMATRIX	mProj;		// �ˉe�ϊ��s��(�]�u�s��)
	XMMATRIX	mTex;		// �e�N�X�`���ϊ��s��(�]�u�s��)
};
