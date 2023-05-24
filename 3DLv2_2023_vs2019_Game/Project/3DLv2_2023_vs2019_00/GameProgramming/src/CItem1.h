#ifndef CITEM1_H
#define CITEM1_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CCollider.h"

/*
エネミークラス
キャラクタクラスを継承
*/
class CItem1 : public CCharacter3 {
public:
	//衝突処理
	void Collision();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	////確認用メソッド　削除予定
	//void CEnemy::Render() {
	//	CCharacter3::Render();
	//	mCollider1.Render();
	//	mCollider2.Render();
	//	mCollider3.Render();
	//}

	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CItem1(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	//更新処理
	void Update();
private:
	//コライダ
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;

};

#endif