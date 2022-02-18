#pragma once
/**
*
* @file		CCamera.h
* @brief	カメラクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
* @date		2022/01/21	カメラマネージャーを作成
*
*/

/** インクルード */
#include <System/Defines.h>
#include <System/Utility/Vector3.h>
#include <memory>

/** 前定義 */
class CTransform;

/** カメラクラス */
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();

	virtual void Update();

protected:
	virtual XMMATRIX CalcProjection();

public:
	CCamera& operator=(const CCamera& camera)
	{
		m_pos	= camera.m_pos;
		m_look	= camera.m_look;
		m_up	= camera.m_up;
		m_screenSize	= camera.m_screenSize;
		m_fNearClip		= camera.m_fNearClip;
		m_fFarClip		= camera.m_fFarClip;
		m_fFov			= camera.m_fFov;
		return *this;
	}

	/**
	* @brief	視点取得
	* @return	Vector3	カメラ視点
	*/
	const Vector3& GetPos() const { return m_pos; }

	/**
	* @brief	注視点取得
	* @return	Vector3	カメラ注視点
	*/
	const Vector3& GetLook() const { return m_look; }

	/**
	* @brief	上方ベクトル取得
	* @return	Vector3	カメラ上方ベクトル
	*/
	const Vector3& GetUp() const { return m_up; }

	/**
	* @brief	スクリーンサイズ取得
	* @return	XMFLOAT2	スクリーンサイズ
	*/
	const XMFLOAT2& GetScreenSize() const { return m_screenSize; }

	/**
	* @brief	縦横比取得
	* @return	float	縦横比
	*/
	float GetAspect()	const { return m_screenSize.x / m_screenSize.y; }
	
	/**
	* @brief	前方クリップ距離取得
	* @return	float	前方クリップ距離
	*/
	float GetNearClip() const { return m_fNearClip; }

	/**
	* @brief	後方クリップ距離取得
	* @return	float	後方クリップ距離
	*/
	float GetFarClip()	const { return m_fFarClip; }

	/**
	* @brief	視野角取得
	* @return	float	視野角
	*/
	float GetFOV()		const { return m_fFov; }

	/**
	* @brief	ビュー行列取得
	* @return	XMFLOAT4X4	ビュー行列
	*/
	const XMFLOAT4X4& GetLookAt() const { return m_lookAt; }
	
	/**
	* @brief	プロジェクション行列取得
	* @return	XMFLOAT4X4	プロジェクション行列
	*/
	const XMFLOAT4X4& GetProjection() const { return m_projection; }
	
	
	/**
	* @brief	ビュー行列取得(計算用)
	* @return	XMMATRIX	ビュー行列
	*/
	const XMMATRIX& GetLookAtMatrix() const { return m_lookAtMatrix; }
	
	/**
	* @brief	プロジェクション行列取得(計算用)
	* @return	XMMATRIX	プロジェクション行列
	*/
	const XMMATRIX& GetProjectionMatrix() const { return m_projectionMatrix; }

	/**
	* @brief	パラメータセット
	* @param	pos		視点
	* @param	look	注視点
	* @param	up		上方ベクトル
	*/
	void SetParameter(Vector3 pos, Vector3 look, Vector3 up)
	{
		m_pos  = pos;
		m_look = look;
		m_up   = up;
	}

	/**
	* @brief	有効ON/OFF
	* @param	enable	有効/無効(true/有効 false/無効)
	*/
	void Enable(bool enable) { m_bIsEnable = enable; }

	/**
	* @brief	有効かどうか
	* @return	bool	有効/無効(true/有効 false/無効)
	*/
	bool IsEnable() const { return m_bIsEnable; }

	/**
	* @brief	対象を追いかけるか
	* @param	chase	true/追いかける , false/追いかけない
	*/
	void Chase(bool chase) { m_bChase = chase; }

	/**
	* @brief	追いかけるターゲットのセット
	* @param	trans	ターゲットのトランスフォーム
	*/
	void SetChaseTarget(std::weak_ptr<CTransform> trans) { m_spTargetTrans = trans; }

	Vector3 CalcScreenPos(Vector3 worldPos);
	Vector3 CalcWorldPos(Vector3 screenPos);

private:
	bool		m_bIsEnable;
	XMFLOAT4X4	m_lookAt;
	XMFLOAT4X4	m_projection;
	XMMATRIX	m_lookAtMatrix;
	XMMATRIX	m_projectionMatrix;
	bool		m_bChase;
	std::weak_ptr<CTransform> m_spTargetTrans;
	
protected:
	Vector3		m_pos;
	Vector3		m_look;
	Vector3		m_up;
	XMFLOAT2	m_screenSize;
	float		m_fNearClip;
	float		m_fFarClip;
	float		m_fFov;
};
