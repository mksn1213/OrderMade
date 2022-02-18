#pragma once
/**
*
* @file		CEffectManager.h
* @brief	エフェクト管理クラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/08	実装開始
*
*/

/** インクルード部 */
#include <System/Utility/Singleton.h>
#include <System/Effect/EffectType.h>

#include <System/Effect/Effekseer/Effekseer.h>
#include <System/Effect/Effekseer/EffekseerRendererDX11.h>

/** ライブラリ */
#pragma comment(lib,"Effekseer.lib")
#pragma comment(lib,"EffekseerRendererDX11.lib")
//#pragma comment(lib,"EffekseerD.lib")
//#pragma comment(lib,"EffekseerRendererDX11D.lib")

#define EFFECT_MANAGER	(CEffectManager::GetInstance())

/** 前定義 */
class Vector3;

/** エフェクト管理クラス */
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
