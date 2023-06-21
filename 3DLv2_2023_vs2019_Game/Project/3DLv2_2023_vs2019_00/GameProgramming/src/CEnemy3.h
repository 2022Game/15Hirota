#ifndef CENEMY3_H
#define CENEMY3_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
//コライダクラスのインクルード
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy3 : public CCharacter3 {
public:
	//コンストラクタ
	CEnemy3();
	//CEnemy3(位置, 回転, 拡縮)
	CEnemy3(CModel* model, const CVector& position, const CVector& rotation,
		const CVector& scale);
	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	CVector mPoint;	//目標地点
	int mHp;	//ヒットポイント
	//モデルデータ
	static CModel sModel;
	//コライダ
	CCollider mCollider;

	//プレイヤーを見つけたかどうか
	bool IsFoundPlayer() const;

	std::vector<CEnemy3*> mEnemy3;	//リスト
	CModel* mpEnemy3Model;	//モデルデータ

	//敵の状態
	enum class EState
	{
		EIDLE,	//待機
		ECHASE,	//追跡
		EATTACK,//攻撃
	};
	//現在の状態
	EState mState;
	//待機
	void UpdateIdle();
	//追跡
	void UpdateChase();
	//攻撃
	void UpdateAttack();
};

#endif
