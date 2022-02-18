#pragma once
/**
*
* @file		CGraphics.h
* @brief	�O���t�B�b�N�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/15	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/DirectX.h>
#include <System/Utility/Singleton.h>
#include <System/Texture/CTexture.h>
#include <System/Graphics/CSamplerState.h>
#include <System/Graphics/CDepthStencilState.h>

#define GRAPHICS (CGraphics::GetInstance())

/**
* @enum		�u�����h���[�h
*/
enum EBlendState
{
	BS_NONE = 0,	// ��������������
	BS_ALPHABLEND,	// ����������
	BS_ADDITIVE,	// ���Z����
	BS_SUBTRACTION,	// ���Z����

	MAX_BLENDSTATE
};

/**
* @enum		�J�����O���[�h
*/
enum ECullMode
{
	CULL_NONE = 0,	// �J�����O���Ȃ�
	CULL_FRONT,		// �O�ʃJ�����O
	CULL_BACK,		// �w�ʃJ�����O

	MAX_CULLMODE
};

/** �O���t�B�b�N�N���X */
class CGraphics final : public Singleton<CGraphics>
{
public:
	/**
	* @enum		ESamplerStateKind
	* @brief	�T���v���[�X�e�[�g�^�C�v
	*/
	enum ESamplerStateKind
	{
		SAMPLER_POINT,
		SAMPLER_LINEAR,

		MAX_SAMPLER
	};

	/**
	* @enum		EDepthStencilKind
	* @brief	�[�x�X�e���V���^�C�v
	*/
	enum EDepthStencilKind
	{
		DEPTHSTENCIL_OFF,
		DEPTHSTENCIL_ON,

		MAX_DEPTHSTENCIL
	};

public:
	HRESULT Init()		final;
	void	Uninit()	final;
	void	BeginDraw();
	void	EndDraw();

	// �����_�[�^�[�Q�b�g
	void SetRenderTarget(CTexture** ppRenderTarget, UINT numView, float* pClearColor = nullptr);
	void SetRenderTargetDefault(float* pClearColor = nullptr);
	void SetShadowRenderTarget(float* pClearColor = nullptr);
	void SetDepthStencilView(CTexture* pDepthStencilView, bool isClear = false);
	void SetDepthStencilViewDefault(bool isClear = false);
	void SetShadowDepthStencilView(bool isClear = false);

	// �T���v���[
	void SetSamplerState(ESamplerStateKind kind);
	void SetSamplerState(CSamplerState *pState);
	CSamplerState* GetSamplerState();

	// �[�x�X�e���V��
	void SetDepthStencilState(EDepthStencilKind kind);
	void SetDepthStencilState(CDepthStencilState* pState);

	CTexture* GetShadowTexture() { return m_pShadowRenderTarget; }
	CTexture* GetDefaulTexture() { return m_pDefRenderTarget; }

private:
	void UpdateTargetView();

	CTexture*			m_pDefRenderTarget;
	CTexture*			m_pDefDepthStencil;
	CTexture*			m_pRenderTarget[4];
	UINT				m_renderTargetNum;
	CTexture*			m_pDepthStencilView;
	CSamplerState*		m_pDefSamplerState[MAX_SAMPLER];
	CSamplerState*		m_pSamplerState;
	CDepthStencilState* m_pDefDepthStencilState[MAX_DEPTHSTENCIL];
	CDepthStencilState* m_pDepthStencilState;

	// �V���h�[�}�b�v�p
	CTexture*			m_pShadowRenderTarget;
	CTexture*			m_pShadowDepthStencil;
};

ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
void SetBlendState(EBlendState nBlendState);
void SetCullMode(ECullMode nCullMode);
