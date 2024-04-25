#ifndef CSAVEPOINT_H
#define CSAVEPOINT_H

#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CObjectBase.h"
class CModel;

// セーブポイントクラス
class CSavePoint : public CObjectBase
{
public:
	CSavePoint(const CVector& pos, const CVector& scale, const CVector& rot);
	~CSavePoint();

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:
	// モデル・素材関連
	// セーブポイントモデル
	CModel* mpSavePointModel;
	// セーブポイントのコライダー
	CColliderLine* mpSaveColLine;

};
#endif