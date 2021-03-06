/**
*
* @file		Shader.cpp
* @brief	シェーダークラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/29	実装開始
* @date		2022/01/18	クラス構造へ変更
*
*/

/** インクルード部 */
#include <System/Graphics/Shader.h>
#include <d3dcompiler.h>
#include <stdio.h>

#pragma comment(lib,"d3dcompiler.lib")

/** 静的メンバ */
VertexShader::ILList VertexShader::m_ilList;

/**
* @brief	コンストラクタ
*/
Shader::Shader(EKind kind)
	: m_eKind(kind)
{

}


/**
* @brief	デストラクタ
*/
Shader::~Shader()
{

}


/**
* @brief	読み込み
* @param	pFileName	ファイル名
*/
HRESULT Shader::Load(const char* pFileName)
{
	HRESULT hr = E_FAIL;

	// ファイル読み込み
	FILE* fp;
	fp = fopen(pFileName, "rb");
	if (!fp) { return hr; }

	// ファイルのサイズを調べる
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリに読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// シェーダー作成
	hr = MakeShader(pData, fileSize);

	// 終了処理
	if (pData) { delete[] pData; }
	return hr;
}

/**
* @brief	コンパイル
* @param	pCode	文字列
*/
HRESULT Shader::Compile(const char* pCode)
{
	static const char* pTargetList[] =
	{
		"vs_5_0",
		"ps_5_0"
	};

	HRESULT		hr;
	ID3DBlob*	pBlob;
	ID3DBlob*	pError;
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompile(pCode, strlen(pCode), nullptr, nullptr, nullptr,
		"main", pTargetList[m_eKind], compileFlag, 0, &pBlob, &pError);
	if (FAILED(hr)) { return hr; }

	// シェーダー作成
	hr = MakeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize());
	SAFE_RELEASE(pBlob);
	SAFE_RELEASE(pError);
	return hr;
}


/**
* @brief	インプットレイアウト解放
*/
void VertexShader::ReleaseInputLayout()
{
	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end())
	{
		SAFE_RELEASE(it->second);
		++it;
	}
}


/**
* @brief	コンストラクタ
*/
VertexShader::VertexShader()
	: Shader(Shader::VertexShader)
	, m_pVertexShader(nullptr)
	, m_pInputLayout(nullptr)
{

}


/**
* @brief	デストラクタ
*/
VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVertexShader);
}


/**
* @brief	割り当て
*/
void VertexShader::Bind()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	pDeviceContext->IASetInputLayout(m_pInputLayout);
}


/**
* @brief	シェーダー作成
* @param	pData	コンパイルされたシェーダーへのポインタ
* @param	size	頂点シェーダーのサイズ
*/
HRESULT VertexShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	auto pDevice = GetDevice();

	// シェーダー作成
	hr = pDevice->CreateVertexShader(pData, size, NULL, &m_pVertexShader);
	if (FAILED(hr)) { return hr; }

	ID3D11ShaderReflection*			pReflection;
	D3D11_SHADER_DESC				shaderDesc;
	D3D11_INPUT_ELEMENT_DESC*		pInputDesc;
	D3D11_SIGNATURE_PARAMETER_DESC	sigDesc;
	std::string						key = "";

	DXGI_FORMAT formats[][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		},
		{
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		},
		{
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	pReflection->GetDesc(&shaderDesc);
	pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	for (int i = 0; i < shaderDesc.InputParameters; ++i)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);
		pInputDesc[i].SemanticName = sigDesc.SemanticName;
		pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:		pInputDesc[i].Format = formats[0][elementCount - 1];	break;
		case D3D_REGISTER_COMPONENT_SINT32:		pInputDesc[i].Format = formats[1][elementCount - 1];	break;
		case D3D_REGISTER_COMPONENT_FLOAT32:	pInputDesc[i].Format = formats[2][elementCount - 1];	break;
		default:																						break;
		}
		pInputDesc[i].InputSlot = 0;
		pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDesc[i].InstanceDataStepRate = 0;

		key += sigDesc.SemanticName;
		key += '0' + sigDesc.SemanticIndex;
	}

	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end())
	{
		if (it->first == key)
		{
			m_pInputLayout = it->second;
			break;
		}
		++it;
	}
	if (it == m_ilList.end())
	{
		hr = pDevice->CreateInputLayout(pInputDesc, shaderDesc.InputParameters, pData, size, &m_pInputLayout);
		if (SUCCEEDED(hr))	m_ilList.insert(ILKey(key, m_pInputLayout));
	}

	SAFE_DELETE_ARRAY(pInputDesc);
	return hr;
}


/**
* @brief	コンストラクタ
*/
PixelShader::PixelShader()
	: Shader(Shader::PixelShader)
	, m_pPixelShader(nullptr)
{

}


/**
* @brief	デストラクタ
*/
PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPixelShader);
}


/**
* @brief	割り当て
*/
void PixelShader::Bind()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
}


/**
* @brief	シェーダー作成
* @param	pData	コンパイルされたシェーダーへのポインタ
* @param	size	ピクセルシェーダーのサイズ
*/
HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(pData, size, NULL, &m_pPixelShader);
	return hr;
}


/**
* @brief	コンストラクタ
*/
ConstantBuffer::ConstantBuffer()
	: m_pBuffer(nullptr)
{

}


/**
* @brief	デストラクタ
*/
ConstantBuffer::~ConstantBuffer()
{

}


/**
* @brief	定数バッファ作成
* @detail	定数バッファの大きさは4バイト区切り
*/
HRESULT ConstantBuffer::Create(UINT size)
{
	HRESULT hr;

	// 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// バッファの作成
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);
	return hr;
}


/**
* @brief	定数バッファ更新
* @param	データへのポインタ
*/
void ConstantBuffer::Write(const void* pData)
{
	// 定数バッファへの書き込み
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}


/**
* @brief	頂点シェーダーステージにセット
* @param	slot	格納位置
*/
void ConstantBuffer::BindVS(UINT slot)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}


/**
* @brief	ピクセルシェーダーステージにセット
* @param	slot	格納位置
*/
void ConstantBuffer::BindPS(UINT slot)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}


/**
* @brief	テクスチャセット
*/
void SetTextureVS(ID3D11ShaderResourceView* pTexture, UINT slot)
{
	GetDeviceContext()->VSSetShaderResources(slot, 1, &pTexture);
}


/**
* @brief	テクスチャセット
*/
void SetTexturePS(ID3D11ShaderResourceView* pTexture, UINT slot)
{
	GetDeviceContext()->PSSetShaderResources(slot, 1, &pTexture);
}