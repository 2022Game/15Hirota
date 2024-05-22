#ifndef CSTAGE3BUTTON_H
#define CSTAGE3BUTTON_H

#include "CColliderMesh.h"
#include "CObjectBase.h"

class CModel;

// ステージ3選択ボタン
class CStage3Button : public CObjectBase
{
public:
	// コンストラクタ
	CStage3Button(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// デストラクタ
	~CStage3Button();

	// インスタンスのポインタの取得
	static CStage3Button* Instance();

	// 衝突処理
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// ステージを選択したことを伝える
	bool IsStage3Button();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

private:
	// インスタンス
	static CStage3Button* spInstance;

	// ステージ1選択ボタン
	CModel* mpStage3ButtonModel;
	// ステージ1選択ボタン
	CColliderMesh* mpColliderMesh;

	// 触れた時に反応するオブジェクトのタグ
	ETag mReactionTag;
	// 触れた時に反応するレイヤー
	ELayer mReactionLayer;

	float mElapsedTime;
	bool mIsStage3Button;
};
#endif