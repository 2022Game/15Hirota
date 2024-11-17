#ifndef CCANLOCKON_H
#define CCANLOCKON_H

#include "CBillBoardImage.h"

// ロックオン可能時のUI
class CCanLockOn : public CBillBoardImage
{
public:
	// コンストラクタ
	CCanLockOn(ETag tag, ETaskPriority, const CVector& pos);
	// デストラクタ
	~CCanLockOn();

	// カラーを設定
	void SetColor(const CColor& color) override;
	// ブレンドタイプを設定
	void SetBlendType(EBlend type);

	// 削除フラグが立っているかどうか
	bool IsDeath() const;

	// 更新
	void Update() override;

private:
	// 元の位置
	CVector mDefaultPos;
	CVector mMoveSpeed;	// 移動速度
	float mElapsedTime;	// 経過時間
	float mAngle;// 角度
	float mDistance;// 距離
	float mSpeed;// 回転スピード
	bool mIsDeath;		// 削除フラグ
};
#endif