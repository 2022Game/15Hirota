#include "CGun.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

#define M1GARAND_O "Character\\Gun_M1Garand\\Gun"
#define M1GARAND_M "Character\\Gun_M1Garand\\Gun"

CGun::CGun()
{
	mpGun = new CModel();
	mpGun->Load("M1GARAND_O", M1GARAND_M);

	// 攻撃判定用のコライダーを作成
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 1.0f, 0.0f)
	);
	// 攻撃判定用のコライダーと衝突判定を行う
	// レイヤーとタグを設定
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
}

CGun::~CGun()
{

}

void CGun::Update()
{

}

void CGun::Render()
{

}

// 衝突処理
void CGun::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用コライダーであれば
	if (self == mpAttackCol)
	{
		// キャラのポインタに変換
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// 相手のコライダーの持ち主がキャラであれば
		if (chara != nullptr)
		{
			//　ダメージを与える
			chara->TakeDamage(1);
		}
	}
}
