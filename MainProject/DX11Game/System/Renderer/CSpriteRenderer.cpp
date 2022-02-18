/**
*
* @file		CSpriteRenderer.cpp
* @brief	�X�v���C�g�����_���[�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CSpriteRenderer.h>
#include <System/Resource/CTextureManager.h>
#include <System/Component/CTransform.h>
#include <System/CPolygon.h>
#include <System/Graphics/CGraphics.h>
#include <System/GameObject/CGameObject.h>
#include <System/Systems/CSpriteRendererSystem.h>
#include <Scene/CSceneManager.h>

/** �ÓI�����o */
const EComponentType CSpriteRenderer::comID = EComponentType::SpriteRenderer;

/**
* @brief	�R���X�g���N�^
*/
CSpriteRenderer::CSpriteRenderer()
	: m_pTexture(nullptr)
	, m_pEffectTexture(nullptr)
	, m_color(Vector3::one())
	, m_fAlpha(1.0f)
	, m_texPos(Vector3::zero())
	, m_texSize(Vector3::one())
	, m_size(Vector3::one())
	, m_localPos(Vector3::zero())
	, m_fParam(0.0f)
{
	SetID(SpriteRenderer);
}


/**
* @brief	�f�X�g���N�^
*/
CSpriteRenderer::~CSpriteRenderer()
{

}


/**
* @brief	������
*/
void CSpriteRenderer::OnCreate()
{
	// �����_���[������
	CRenderer::OnCreate();
	// �V�F�[�_�[�Z�b�g
	m_spGameObject.lock()->SetShader(Simple2DVS, Simple2DPS);
	// �V�X�e�����X�g�Ɋi�[
	CSpriteRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	�j����
*/
void CSpriteRenderer::OnDestroy()
{
	// �V�X�e�����珜�O
	CSpriteRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	�X�V����
*/
void CSpriteRenderer::Update()
{

}


/**
* @brief	�`�揈��
*/
void CSpriteRenderer::Draw(ID3D11DeviceContext* pDC)
{
	// Z�o�b�t�@����
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_OFF);
	// �u�����h�X�e�[�g
	SetBlendState(BS_ALPHABLEND);

	const auto& transform = m_spTransform.lock();

	// ���W
	auto polygon = POLYGON;
	auto pos = transform->GetPosition() + m_localPos;
	polygon->SetPos(pos->x, pos->y);
	// �p�x
	polygon->SetAngle(transform->GetRotation()->z);
	// �T�C�Y
	polygon->SetSize(m_size->x, m_size->y);
	// �F
	polygon->SetColor(m_color.m_vector);
	// �A���t�@�l
	polygon->SetAlpha(m_fAlpha);
	// �e�N�X�`��
	polygon->SetTexture(m_pTexture);
	// ���ʃe�N�X�`��
	polygon->SetEffectTexture(m_pEffectTexture);
	// �}���`�e�N�X�`��
	if (m_spGameObject.lock()->GetPSKind() == EPixelShaderKind::MultiTexturePS)
	{
		polygon->SetParam(m_fParam);
		polygon->SetMultiTexture(m_pMultiTexture, m_pMultiTexture2);
	}
	// �e�N�X�`�����W
	polygon->SetUV(m_texPos->x, m_texPos->y);
	// �e�N�X�`���T�C�Y
	polygon->SetFrameSize(m_texSize->x, m_texSize->y);

	// �`�揈��
	polygon->Draw(pDC,m_spGameObject);

	// �u�����h�X�e�[�g
	SetBlendState(BS_NONE);
	// Z�o�b�t�@�L��
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);
}


/**
* @brief	�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`���^�C�v
*/
void CSpriteRenderer::SetTexture(ETexture texture)
{
	if (m_pTexture != nullptr)	m_pTexture = nullptr;
	m_pTexture = TEXTURE_MANAGER->GetTexture(texture);
}


/**
* @brief	�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`�����\�[�X
*/
void CSpriteRenderer::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_pTexture = texture;
}


/**
* @brief	���ʃe�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`���^�C�v
*/
void CSpriteRenderer::SetEffectTexture(ETexture texture)
{
	if (m_pEffectTexture != nullptr)	m_pEffectTexture= nullptr;
	m_pEffectTexture = TEXTURE_MANAGER->GetTexture(texture);
}


/**
* @brief	���ʃe�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`�����\�[�X
*/
void CSpriteRenderer::SetEffectTexture(ID3D11ShaderResourceView* texture)
{
	m_pEffectTexture = texture;
}


/**
* @brief	�}���`�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`���^�C�v
* @param	nNo			���蓖�Ĕԍ�
*/
void CSpriteRenderer::SetMultiTexture(ETexture texture, int nNo)
{
	if (nNo == 0)
	{
		if (m_pMultiTexture != nullptr)		m_pMultiTexture = nullptr;
		m_pMultiTexture = TEXTURE_MANAGER->GetTexture(texture);
	}
	else if (nNo == 1)
	{
		if (m_pMultiTexture2 != nullptr)	m_pMultiTexture2 = nullptr;
		m_pMultiTexture2 = TEXTURE_MANAGER->GetTexture(texture);
	}
}


/**
* @brief	�}���`�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`�����\�[�X
* @param	nNo			���蓖�Ĕԍ�
*/
void CSpriteRenderer::SetMultiTexture(ID3D11ShaderResourceView* texture, int nNo)
{
	if (nNo == 0)		m_pMultiTexture = texture;
	else if (nNo == 1)	m_pMultiTexture2 = texture;
}


/**
* @brief	�}���`�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`���^�C�v
* @param	texture2	�Z�b�g����e�N�X�`���^�C�v2
*/
void CSpriteRenderer::SetMultiTexture(ETexture texture, ETexture texture2)
{
	if (m_pMultiTexture != nullptr)		m_pMultiTexture = nullptr;
	m_pMultiTexture = TEXTURE_MANAGER->GetTexture(texture);
	if (m_pMultiTexture2 != nullptr)	m_pMultiTexture2 = nullptr;
	m_pMultiTexture2 = TEXTURE_MANAGER->GetTexture(texture2);
}


/**
* @brief	�}���`�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`�����\�[�X
* @param	texture2	�Z�b�g����e�N�X�`�����\�[�X2
*/
void CSpriteRenderer::SetMultiTexture(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* texture2)
{
	m_pMultiTexture = texture;
	m_pMultiTexture2 = texture2;
}
