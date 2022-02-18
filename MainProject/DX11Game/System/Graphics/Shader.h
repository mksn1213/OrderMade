#pragma once
/**
*
* @file		Shader.h
* @brief	�V�F�[�_�[�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/29	�����J�n
* @date		2022/01/18	�N���X�\���֕ύX
*
*/

/** �C���N���[�h�� */
#include <System/Defines.h>
#include <string>
#include <map>

/** �V�F�[�_�[��{�N���X */
class Shader
{
protected:
	/**
	* @enum		EKind
	* @brief	�V�F�[�_�[�̎��
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

/** ���_�V�F�[�_�[�N���X */
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

/** �s�N�Z���V�F�[�_�[�N���X */
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

/** �萔�o�b�t�@�N���X */
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

// �e�N�X�`��
void SetTextureVS(ID3D11ShaderResourceView* pTexture, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* pTexture, UINT slot = 0);