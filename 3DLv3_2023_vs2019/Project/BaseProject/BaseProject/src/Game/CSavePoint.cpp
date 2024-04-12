#include "CSavePoint.h"
#include "CPlayer.h"

// コストラクタ
CSavePoint::CSavePoint(const CVector& pos, const CVector& scale, const CVector& rot)
{
	// セーブポイントモデル取得
	mpSavePointModel = CResourceManager::Get<CModel>("SavePoint");

	// セーブポイントのコライダー作成
	mpSaveColLine = new CColliderLine
	(
		this, ELayer::eSavePoint,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	mpSaveColLine->SetCollisionLayers({ ELayer::ePlayer });
	mpSaveColLine->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// デストラクタ
CSavePoint::~CSavePoint()
{
	SAFE_DELETE(mpSaveColLine);
}

// 更新処理
void CSavePoint::Update()
{

}

// 描画処理
void CSavePoint::Render()
{
	mpSavePointModel->SetColor(mColor);
	mpSavePointModel->Render(Matrix());
}