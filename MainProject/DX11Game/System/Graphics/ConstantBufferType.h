#pragma once
#include <System/Defines.h>

struct SHADER_GLOBAL 
{
	XMMATRIX	mWorld;			// ワールド行列(転置行列)
	XMMATRIX	mView;
	XMMATRIX	mProj;
	XMMATRIX	mTex;		// テクスチャ行列(転置行列)
	XMVECTOR	vEye;		// 視点座標
	XMVECTOR	vLightDir;	// 光源方向
	XMVECTOR	vLa;		// 光源色(アンビエント)
	XMVECTOR	vLd;		// 光源色(ディフューズ)
	XMVECTOR	vLs;		// 光源色(スペキュラ)
};

// マテリアル (シェーダ用)
struct SHADER_MATERIAL 
{
	XMVECTOR	vAmbient;	// アンビエント色
	XMVECTOR	vDiffuse;	// ディフューズ色
	XMVECTOR	vSpecular;	// スペキュラ色
	XMVECTOR	vEmissive;	// エミッシブ色
	XMVECTOR	vFlags;		// テクスチャ有無
};

// シェーダに渡すボーン行列配列
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
	XMMATRIX	mWorld;		// ワールド行列(転置行列)
	XMMATRIX	mView;
	XMMATRIX	mProj;
	XMMATRIX	mTex;		// テクスチャ行列(転置行列)
};
struct SHADER_GLOBAL2_MESH
{
	XMVECTOR	vEye;		// 視点座標
	// 光源
	XMVECTOR	vLightDir;	// 光源方向
	XMVECTOR	vLa;		// 光源色(アンビエント)
	XMVECTOR	vLd;		// 光源色(ディフューズ)
	XMVECTOR	vLs;		// 光源色(スペキュラ)
	// マテリアル
	XMVECTOR	vAmbient;	// アンビエント色(+テクスチャ有無)
	XMVECTOR	vDiffuse;	// ディフューズ色
	XMVECTOR	vSpecular;	// スペキュラ色(+スペキュラ強度)
	XMVECTOR	vEmissive;	// エミッシブ色
};

struct SHADER_GLOBAL_POLYGON
{
	XMMATRIX	mWorld;		// ワールド変換行列(転置行列)
	XMMATRIX	mView;		// ビュー変換行列(転置行列)
	XMMATRIX	mProj;		// 射影変換行列(転置行列)
	XMMATRIX	mTex;		// テクスチャ変換行列(転置行列)
};
