#pragma once
/**
*
* @file		CMeshRenderer.h
* @brief	メッシュレンダラークラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/05	実装開始
* @date		2022/01/15	シェーダーをリストで管理
*
*/

/** インクルード部 */
#include <System/Renderer/CRenderer.h>
#include <System/Defines.h>
#include <System/Resource/TextureID.h>
#include <System/Utility/Vector3.h>
#include <System/Graphics/Shader.h>

/** 列挙体 */
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
	TT_NOAFFECT = 0,	// 全て
	TT_OPACITYONLY,		// 不透明のみ
	TT_TRANSLUCENTONLY,	// 半透明のみ

	MAX_TRANSLUCENTTYPE
};

/** マテリアルクラス */
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

/** メッシュクラス */
class CMesh
{
public:
	CMesh();
	~CMesh();

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	int m_nNumVertex;	// 総頂点数
	int m_nNumIndex;	// 総インデックス数

	ID3D11ShaderResourceView*	m_pBaseTexture;		// テクスチャ
	ID3D11ShaderResourceView*	m_pNormalTexture;	// 法線テクスチャ
	XMFLOAT4X4					m_mtxTexture;		// テクスチャマトリックス

	CMeshMaterial*		m_pMaterial;			// マテリアル
	EPrimitiveType		m_ePrimitiveType;		// プリミティブ型
	ETranslucentType	m_eTranslucentType;		// 描画タイプ
	float m_fAlpha;								// 頂点カラーα最小値
};

/** メッシュレンダラークラス */
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

	static CMeshMaterial				m_material;				// マテリアル	
	bool								m_bBillboard;			// ビルボードかどうか

public:
	// コンポーネントID
	static const EComponentType comID;
};