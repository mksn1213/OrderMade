/**
*
* @file		Shader.cpp
* @brief	�V�F�[�_�[�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/29	�����J�n
* @date		2022/01/18	�N���X�\���֕ύX
*
*/

/** �C���N���[�h�� */
#include <System/Graphics/Shader.h>
#include <d3dcompiler.h>
#include <stdio.h>

#pragma comment(lib,"d3dcompiler.lib")

/** �ÓI�����o */
VertexShader::ILList VertexShader::m_ilList;

/**
* @brief	�R���X�g���N�^
*/
Shader::Shader(EKind kind)
	: m_eKind(kind)
{

}


/**
* @brief	�f�X�g���N�^
*/
Shader::~Shader()
{

}


/**
* @brief	�ǂݍ���
* @param	pFileName	�t�@�C����
*/
HRESULT Shader::Load(const char* pFileName)
{
	HRESULT hr = E_FAIL;

	// �t�@�C���ǂݍ���
	FILE* fp;
	fp = fopen(pFileName, "rb");
	if (!fp) { return hr; }

	// �t�@�C���̃T�C�Y�𒲂ׂ�
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// �������ɓǂݍ���
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// �V�F�[�_�[�쐬
	hr = MakeShader(pData, fileSize);

	// �I������
	if (pData) { delete[] pData; }
	return hr;
}

/**
* @brief	�R���p�C��
* @param	pCode	������
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

	// �V�F�[�_�[�쐬
	hr = MakeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize());
	SAFE_RELEASE(pBlob);
	SAFE_RELEASE(pError);
	return hr;
}


/**
* @brief	�C���v�b�g���C�A�E�g���
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
* @brief	�R���X�g���N�^
*/
VertexShader::VertexShader()
	: Shader(Shader::VertexShader)
	, m_pVertexShader(nullptr)
	, m_pInputLayout(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVertexShader);
}


/**
* @brief	���蓖��
*/
void VertexShader::Bind()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	pDeviceContext->IASetInputLayout(m_pInputLayout);
}


/**
* @brief	�V�F�[�_�[�쐬
* @param	pData	�R���p�C�����ꂽ�V�F�[�_�[�ւ̃|�C���^
* @param	size	���_�V�F�[�_�[�̃T�C�Y
*/
HRESULT VertexShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	auto pDevice = GetDevice();

	// �V�F�[�_�[�쐬
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
* @brief	�R���X�g���N�^
*/
PixelShader::PixelShader()
	: Shader(Shader::PixelShader)
	, m_pPixelShader(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPixelShader);
}


/**
* @brief	���蓖��
*/
void PixelShader::Bind()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
}


/**
* @brief	�V�F�[�_�[�쐬
* @param	pData	�R���p�C�����ꂽ�V�F�[�_�[�ւ̃|�C���^
* @param	size	�s�N�Z���V�F�[�_�[�̃T�C�Y
*/
HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(pData, size, NULL, &m_pPixelShader);
	return hr;
}


/**
* @brief	�R���X�g���N�^
*/
ConstantBuffer::ConstantBuffer()
	: m_pBuffer(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
ConstantBuffer::~ConstantBuffer()
{

}


/**
* @brief	�萔�o�b�t�@�쐬
* @detail	�萔�o�b�t�@�̑傫����4�o�C�g��؂�
*/
HRESULT ConstantBuffer::Create(UINT size)
{
	HRESULT hr;

	// �쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// �o�b�t�@�̍쐬
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);
	return hr;
}


/**
* @brief	�萔�o�b�t�@�X�V
* @param	�f�[�^�ւ̃|�C���^
*/
void ConstantBuffer::Write(const void* pData)
{
	// �萔�o�b�t�@�ւ̏�������
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}


/**
* @brief	���_�V�F�[�_�[�X�e�[�W�ɃZ�b�g
* @param	slot	�i�[�ʒu
*/
void ConstantBuffer::BindVS(UINT slot)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}


/**
* @brief	�s�N�Z���V�F�[�_�[�X�e�[�W�ɃZ�b�g
* @param	slot	�i�[�ʒu
*/
void ConstantBuffer::BindPS(UINT slot)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	pDeviceContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}


/**
* @brief	�e�N�X�`���Z�b�g
*/
void SetTextureVS(ID3D11ShaderResourceView* pTexture, UINT slot)
{
	GetDeviceContext()->VSSetShaderResources(slot, 1, &pTexture);
}


/**
* @brief	�e�N�X�`���Z�b�g
*/
void SetTexturePS(ID3D11ShaderResourceView* pTexture, UINT slot)
{
	GetDeviceContext()->PSSetShaderResources(slot, 1, &pTexture);
}