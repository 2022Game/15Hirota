#ifndef CBULLET_H
#define CBULLET_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
//三角形のインクルード
#include "CTriangle.h"
//コライダクラスのインクルード
#include "CCollider.h"

/*
弾クラス
三角形を飛ばす
*/
class CBullet : public CCharacter3 {
public:
	//幅と奥行きの設定
	//Set(幅、奥行き)
	void Set(float w, float d);

	CBullet();

	//更新
	void Update();
	//描画
	void Render();

private:
	//三角形
	CTriangle mT;
	//生存時間
	int mLife;
private:
	//コライダ
	CCollider mCollider;
};

#endif