#ifndef CCHARACTER3_H
#define CCHARACTER3_H
//変換行列クラスのインクルード
#include "CTransform.h"
//モデルクラスのインクルード
#include "CModel.h"
#include "CTask.h"
#include "TaskPauseType.h"
#include "TaskPriority.h"
//コライダクラスの宣言
class CCollider;

/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter3 : public CTransform, public CTask {
public:
	enum ETag
	{
		EZERO,			//初期値
		EPLAYER,		//プレイヤー
		EENEMY,			//敵
		EBULLETPLAYER,	//プレイヤー弾
		EBULLETENEMY,	//敵弾
	};
	enum class EState
	{
		EJUMP,	//ジャンプ
	};
	//タグの取得
	ETag Tag();

	//衝突処理
	virtual void Collision(CCollider* m, CCollider* o) {}
	//コンストラクタ
	CCharacter3();
	//コンストラクタ
	CCharacter3(int priority);
	//デストラクタ
	~CCharacter3();
	//モデルの設定
	//Model(モデルクラスのポインタ)
	void Model(CModel* m);
	//描画処理
	void Render();
	//ダメージを与える
	virtual void TakeDamage(int damege);
	//キャラクターが死んでいるかどうか
	bool IsDeath();
private:
	
protected:
	ETag mTag;	//タグ
	CModel* mpModel; //モデルのポインタ

	int mHp;
	int mStamina;
};

#endif