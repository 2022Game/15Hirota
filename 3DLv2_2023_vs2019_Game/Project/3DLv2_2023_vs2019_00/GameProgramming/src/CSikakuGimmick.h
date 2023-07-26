#ifndef CSIKAKUGIMMICK_H
#define CSIKAKUGIMMICK_H

#include "CTask.h"
#include "CSikaku.h"
#include "CTransform.h"
#include "CModel.h"
#include "CCharacter3.h"

class CSikakuGimmick :public CTask
{
public:
	CSikakuGimmick();
	~CSikakuGimmick();

	//位置の取得
	const CVector& Position() const;
	//Position(位置)
	void Position(const CVector& v);

	//更新処理
	void Update();
private:
	CColliderMesh mColliderMesh;	//Fieldの当たり判定用コライダ
	std::vector<CSikaku*> mSikakus;	//リスト
	std::vector<CSikaku*> mMovingSikakus; // 移動させたい四角のリスト
	CModel* mpSikakuModel;	//モデルデータ
	CSikaku* mMovingSikaku;  // 移動させたい四角を保持するメンバ変数

	//初期化処理
	void Init();
	//リストに追加
	void CreateSikaku(CVector& pos, CVector& rot, CVector& scale);

protected:
	CVector mPosition;	//位置

	int mMoveCounter;	//移動カウンター
	int mMoveDirection;	//反転カウント
	bool mReverseMove; // 移動方向を反転させるフラグ
};
#endif