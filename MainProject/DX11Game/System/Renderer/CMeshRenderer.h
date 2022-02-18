#pragma once
/**
*
* @file		CMeshRenderer.h
* @brief	���b�V�������_���[�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/05	�����J�n
* @date		2022/01/15	�V�F�[�_�[�����X�g�ŊǗ�
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CRenderer.h>
#include <System/Defines.h>
#include <System/Resource/TextureID.h>
#include <System/Utility/Vector3.h>
#include <System/Graphics/Shader.h>

/** �񋓑� */
enum EPrimitiveType
{
	PT_UNDEFINED = 0,
	PT_POINT,
	PT_LINE,
	PT_LINESTRIP,
	PT_TRIANGLE,
	PT_TRIANGLESTRIP,

	MAX_PRIMITIVETYPE
};
enum ETranslucentType
{
	TT_NOAFFECT = 0,	// �S��
	TT_OPACITYONLY,		// �s�����̂�
	TT_TRANSLUCENTONLY,	// �������̂�

	MAX_TRANSLUCENTTYPE
};

/** �}�e���A���N���X */
class CMeshMaterial
{
public:
	CMeshMaterial();

	XMFLOAT4	m_diffuse;
	XMFLOAT4	m_ambient;
	XMFLOAT4	m_specular;
	XMFLOAT4	m_emissive;
	float		m_power;
};

/** ���b�V���N���X */
class CMesh
{
public:
	CMesh();
	~CMesh();

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	int m_nNumVertex;	// �����_��
	int m_nNumIndex;	// ���C���f�b�N�X��

	ID3D11ShaderResourceView*	m_pBaseTexture;		// �e�N�X�`��
	ID3D11ShaderResourceView*	m_pNormalTexture;	// �@���e�N�X�`��
	XMFLOAT4X4					m_mtxTexture;		// �e�N�X�`���}�g���b�N�X

	CMeshMaterial*		m_pMaterial;			// �}�e���A��
	EPrimitiveType		m_ePrimitiveType;		// �v���~�e�B�u�^
	ETranslucentType	m_eTranslucentType;		// �`��^�C�v
	float m_fAlpha;								// ���_�J���[���ŏ��l
};

/** ���b�V�������_���[�N���X */
class CMeshRenderer final :public CRenderer
{
public:
	CMeshRenderer();
	virtual ~CMeshRenderer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	void Draw(ID3D11DeviceContext* pDC)	override;

	void BillboardUpdateMatrix();

	static HRESULT	InitMesh();
	static void		UninitMesh();
	HRESULT			MakeMeshVertex(ID3D11Device* pDevice, VERTEX_3D vertexWk[], int indexWk[]);

	HRESULT MakePlane(float texPos = 1.0f);
	HRESULT MakeBillboard();
	HRESULT MakeBox(Vector3 size, Vector3 center = Vector3::zero());
	HRESULT MakeSphere(Vector3 size, Vector3 center = Vector3::zero());

	void	SetBaseTexture(ETexture type);
	void	SetNormalTexture(const char* filename);

	CMesh*	GetMesh() { return m_pMesh; }
	void	SetColor(XMFLOAT4 color)	{ m_pMesh->m_pMaterial->m_diffuse = color; }
	void	SetAlpha(float fAlpha)		{ m_pMesh->m_pMaterial->m_diffuse.w = fAlpha; }

private:
	CMesh* m_pMesh;

	static CMeshMaterial				m_material;				// �}�e���A��	
	bool								m_bBillboard;			// �r���{�[�h���ǂ���

public:
	// �R���|�[�l���gID
	static const EComponentType comID;
};