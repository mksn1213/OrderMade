#pragma once
/**
*
* @file		CPolyton.h
* @brief	�|���S���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2022/01/15	�V���O���g���p��
* @date		2022/01/21	�V�F�[�_�[�����X�g�ŊǗ�
*
*/

/** �C���N���[�h�� */
#include <System/DirectX.h>
#include <System/Utility/Singleton.h>
#include <System/Defines.h>
#include <iostream>

#define POLYGON	(CPolygon::GetInstance())

class CGameObject;
/** �|���S���N���X */
class CPolygon :public Singleton<CPolygon>
{
	//SINGLETON_CONSTRACTOR(CPolygon);
public:
	CPolygon();
	virtual ~CPolygon();

	HRESULT Init()		final;
	void	Uninit()	final;
	void Draw(ID3D11DeviceContext* pDeviceContext, std::weak_ptr<CGameObject> spObj);
	void SetTexture(ID3D11ShaderResourceView* pTexture);
	void SetEffectTexture(ID3D11ShaderResourceView* pTexture);
	void SetMultiTexture(ID3D11ShaderResourceView* pTexture);
	void SetMultiTexture(ID3D11ShaderResourceView* pTexture, ID3D11ShaderResourceView* pTexture2);
	void SetParam(float fParam) { m_fParam = fParam; }
	void SetPos(float fX, float fY);
	void SetSize(float fScaleX, float fScaleY);
	void SetAngle(float fAngle);
	void SetUV(float fU, float fV);
	void SetFrameSize(float fWidth, float fHeight);
	void SetColor(float fRed, float fGreen, float fBlue);
	void SetColor(XMFLOAT3 vColor);
	void SetAlpha(float fAlpha);
	void SetColor(float fRed, float fGreen, float fBlue, float fAlpha);
	void SetColor(XMFLOAT4 vColor);

private:
	ID3D11ShaderResourceView*	m_pTexture;			// �e�N�X�`��
	ID3D11ShaderResourceView*	m_pEffectTexture;	// ���ʃe�N�X�`��
	ID3D11ShaderResourceView*	m_pMultiTexture;	// �}���`�e�N�X�`��
	ID3D11ShaderResourceView*	m_pMultiTexture2;	// �}���`�e�N�X�`��2
	float						m_fParam;			// �V�F�[�_�[�p�p�����[�^

	VERTEX_2D m_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	XMFLOAT3 m_vPos;						// �|���S���̈ړ���
	XMFLOAT3 m_vAngle;						// �|���S���̉�]��
	XMFLOAT3 m_vScale;						// �|���S���̃T�C�Y
	XMFLOAT4 m_vColor;						// �|���S���̒��_�J���[
	bool m_bInvalidate;						// ���_�f�[�^�X�V�t���O

	XMFLOAT2 m_vPosTexFrame;				// UV���W
	XMFLOAT2 m_vSizeTexFrame;				// �e�N�X�`�����o�T�C�Y

	// �X�V��ϐ�
	ID3D11Buffer*		m_pVertexBuffer;	// ���_�o�b�t�@

	XMFLOAT4X4 m_mProj;						// �ˉe�ϊ��s��
	XMFLOAT4X4 m_mView;						// �r���[�ϊ��s��
	XMFLOAT4X4 m_mWorld;					// ���[���h�ϊ��s��
	XMFLOAT4X4 m_mTex;						// �e�N�X�`���ϊ��s��

private:
	HRESULT MakeVertex(ID3D11Device* pDevice);
	void SetVertex(void);
};
