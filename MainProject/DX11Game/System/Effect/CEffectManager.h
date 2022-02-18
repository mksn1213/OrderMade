#pragma once
/**
*
* @file		CEffectManager.h
* @brief	�G�t�F�N�g�Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/08	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <System/Effect/EffectType.h>

#include <System/Effect/Effekseer/Effekseer.h>
#include <System/Effect/Effekseer/EffekseerRendererDX11.h>

/** ���C�u���� */
#pragma comment(lib,"Effekseer.lib")
#pragma comment(lib,"EffekseerRendererDX11.lib")
//#pragma comment(lib,"EffekseerD.lib")
//#pragma comment(lib,"EffekseerRendererDX11D.lib")

#define EFFECT_MANAGER	(CEffectManager::GetInstance())

/** �O��` */
class Vector3;

/** �G�t�F�N�g�Ǘ��N���X */
class CEffectManager final : public Singleton<CEffectManager>
{
public:
	CEffectManager();
	~CEffectManager();

	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();

	void Play(EEffectType type, Vector3 pos);
	void StopAll();

private:
	EffekseerRendererDX11::RendererRef	m_renderer;
	Effekseer::ManagerRef				m_manager;
	Effekseer::EffectRef				m_effect[MaxEffect];
	Effekseer::Handle					m_handle;
};
