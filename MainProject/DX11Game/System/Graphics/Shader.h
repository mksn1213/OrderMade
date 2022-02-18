#pragma once
/**
*
* @file		Shader.h
* @brief	シェーダークラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/29	実装開始
* @date		2022/01/18	クラス構造へ変更
*
*/

/** インクルード部 */
#include <System/Defines.h>
#include <string>
#include <map>

/** シェーダー基本クラス */
class Shader
{
protected:
	/**
	* @enum		EKind
	* @brief	シェーダーの種類
	*/
	enum EKind
	{
		VertexShader,
		PixelShader
	};
public:
	Shader(EKind kind);
	virtual ~Shader();

	HRESULT Load(const char* pFileName);
	HRESULT Compile(const char* pCode);

	virtual void Bind() = 0;

protected:
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	EKind m_eKind;
};

/** 頂点シェーダークラス */
class VertexShader :public Shader
{
private:
	using ILKey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::map<std::string, ID3D11InputLayout*>;
public:
	VertexShader();
	virtual ~VertexShader();

	void Bind();
	static void ReleaseInputLayout();

protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11InputLayout*	m_pInputLayout;
	static ILList		m_ilList;
};

/** ピクセルシェーダークラス */
class PixelShader : public Shader
{
public:
	PixelShader();
	virtual ~PixelShader();

	void Bind();

protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	ID3D11PixelShader*	m_pPixelShader;
};

/** 定数バッファクラス */
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	HRESULT Create(UINT size);
	void Write(const void* pData);
	void BindVS(UINT slot);
	void BindPS(UINT slot);
	ID3D11Buffer* GetBuffer() { return m_pBuffer; }

private:
	ID3D11Buffer*	m_pBuffer;
};

// テクスチャ
void SetTextureVS(ID3D11ShaderResourceView* pTexture, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* pTexture, UINT slot = 0);