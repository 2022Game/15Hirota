#ifndef CSIKAKUGIMMICK_H
#define CSIKAKUGIMMICK_H

#include "CTask.h"
#include "CSikaku.h"
#include "CTransform.h"

class CSikakuGimmick :public CTask
{
private:
	std::vector<CSikaku*> mSikakus;	//リスト
	std::vector<CSikaku*> mMovingSikakus; // 移動させたい四角のリスト
	CModel* mpSikakuModel;	//モデルデータ
	CSikaku* mMovingSikaku;  // 移動させたい四角を保持するメンバ変数

	//初期化処理
	void Init();
	//リストに追加
	void CreateSikaku(CVector& pos, CVector& rot, CVector& scale);

	CVector mVelocity;	//重力加速度

protected:
	CVector mPosition;	//位置

	int mMoveCounter;	//反転フラグ
	int mMoveDirection;	//反転カウント
	bool mReverseMove; // 移動方向を反転させるフラグ

public:
	CSikakuGimmick();
	~CSikakuGimmick();

	//位置の取得
	const CVector& Position() const;
	//Position(位置)
	void Position(const CVector& v);

	//const CVector& Position();
	void Velocity(const CVector& v);

	//更新処理
	void Update();
};
#endif