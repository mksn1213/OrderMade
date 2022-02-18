#pragma once
/**
*
* @file		CSpriteRenderer.h
* @brief	�X�v���C�g�����_���[�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CRenderer.h>
#include <System/Defines.h>
#include <System/Utility/Vector3.h>
#include <System/Resource/TextureID.h>

/** �X�v���C�g�����_���[�N���X */
class CSpriteRenderer final : public CRenderer
{
public:
	CSpriteRenderer();
	virtual ~CSpriteRenderer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	void Draw(ID3D11DeviceContext* pDC)	override;

	void SetTexture(ETexture texture);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetEffectTexture(ETexture texture);
	void SetEffectTexture(ID3D11ShaderResourceView* texture);
	void SetMultiTexture(ETexture texture, int nNo = 0);
	void SetMultiTexture(ID3D11ShaderResourceView* texture, int nN = 0);
	void SetMultiTexture(ETexture texture, ETexture texture2);
	void SetMultiTexture(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* texture2);

	/**
	* @brief	�F�ύX
	* @param	color	�ύX��̐F
	*/
	void SetColor(Vector3 color) { m_color = color; }

	/**
	* @brief	�F�ύX
	* @param	color	�ύX��̐F
	* @param	fAlpha	�A���t�@�l
	*/
	void SetColor(Vector3 color, float fAlpha)
	{
		m_color = color;
		m_fAlpha = fAlpha;
	}

	/**
	* @brief	�F�ύX
	* @param	r	��
	* @param	g	��
	* @param	b	��
	*/
	void SetColor(float r, float g, float b)
	{
		m_color->x = r;
		m_color->y = g;
		m_color->z = b;
	}

	/**
	* @brief	�F�ύX
	* @param	r	��
	* @param	g	��
	* @param	b	��
	* @param	a	�A���t�@�l
	*/
	void SetColor(float r, float g, float b, float fAlpha)
	{
		m_color->x = r;
		m_color->y = g;
		m_color->z = b;
		m_fAlpha = fAlpha;
	}

	/**
	* @brief	�����x�ύX
	* @param	fAlpha		�����x
	*/
	void SetAlpha(float fAlpha) 
	{ 
		m_fAlpha = fAlpha; 
	}

	/**
	* @brief	�`��T�C�Y�Z�b�g
	* @param	size	�Z�b�g����`��T�C�Y
	*/
	void SetDrawSize(Vector3 size) { m_size = size; }

	/**
	* @brief	�`��T�C�Y�擾
	* @param	Vector3		�`��T�C�Y
	*/
	Vector3 GetDrawSize() { return m_size; }

	/**
	* @brief	���[�J�����W�Z�b�g
	* @param	localPos	���[�J�����W
	*/
	void SetLocalPos(Vector3 localPos) { m_localPos = localPos; }

	/**
	* @brief	�e�N�X�`���T�C�Y�Z�b�g
	* @param	texSize		�e�N�X�`���T�C�Y
	*/
	void SetTexSize(Vector3 texSize) { m_texSize = texSize; }

	/**
	* @brief	�e�N�X�`�����W�Z�b�g
	* @param	texPos		�e�N�X�`�����W
	*/
	void SetTexPos(Vector3 texPos) { m_texPos = texPos; }

	/**
	* @brief	�V�F�[�_�[�p�����[�^�Z�b�g
	* @param	fParam	�p�����[�^
	*/
	void SetParam(float fParam) { m_fParam = fParam; }

private:
	// �e�N�X�`��
	ID3D11ShaderResourceView*	m_pTexture;
	// ���ʃe�N�X�`��
	ID3D11ShaderResourceView*	m_pEffectTexture;
	// �}���`�e�N�X�`��
	ID3D11ShaderResourceView*	m_pMultiTexture;
	// �}���`�e�N�X�`��2
	ID3D11ShaderResourceView*	m_pMultiTexture2;;
	// �F���
	Vector3						m_color;
	// �A���t�@�l
	float						m_fAlpha;
	// �e�N�X�`�����W
	Vector3						m_texPos;
	// �e�N�X�`���T�C�Y
	Vector3						m_texSize;
	// �`��T�C�Y
	Vector3						m_size;
	// ���[�J�����W
	Vector3						m_localPos;
	// �V�F�[�_�[�p�p�����[�^
	float						m_fParam;

public:
	static const EComponentType comID;
};