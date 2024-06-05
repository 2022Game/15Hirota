#ifndef CPLAYERSMOKE_H
#define CPLAYERSMOKE_H

#include "CTask.h"
#include "CObjectBase.h"
#include <list>

class CSmoke;

// プレイヤーの煙クラス
class CPlayerSmoke : public CTask
{
public:
	// コンストラクタ
	CPlayerSmoke(CObjectBase* owner, const CMatrix* attach,
		const CVector& offsetPos = CVector::zero,
		const CMatrix& offsetRot = CMatrix::identity);
	// デストラクタ
	~CPlayerSmoke();

	// 煙をを発生開始
	void Start();
	// 煙を停止
	void Stop();

	// 煙を発射しているかどうか
	bool IsThrowing() const;

	// 発射時のオフセット位置を設定
	void SetThrowOffsetPos(const CVector& pos);
	// 発射時のオフセット回転値を設定
	void SetThrowOffsetRot(const CMatrix& rot);


	// 更新
	void Update() override;

private:
	// 煙のエフェクトを作成
	void CreateSmoke();

	// 煙の発射位置を取得
	CVector GetThrowPos() const;
	// 煙の発射方向を取得
	CVector GetThrowDir() const;

	// 煙のエフェクトのリスト
	std::list<CSmoke*> mSmoke;
	CObjectBase* mpOwner;		// このエフェクトの持ち主
	const CMatrix* mpAttachMtx;	// エフェクトをアタッチする行列
	CVector mThrowOffsetPos;	// 発射時のオフセット位置
	CMatrix mThrowOffsetRot;	// 発射時のオフセット回転値
	float mElapsedTime;			// 経過時間計測用
	bool mIsThrowing;			// 煙を発射しているか
};
#endif