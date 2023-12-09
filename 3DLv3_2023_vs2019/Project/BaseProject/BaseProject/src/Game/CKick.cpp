#include "CKick.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

CKick::CKick()
{
	// 右足にプレイヤーにダメージを与えるコライダーを作成
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		0.5f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });

	mpAttackCol->SetEnable(false);
}

CKick::~CKick()
{

}

void CKick::Update()
{

}

void CKick::Render()
{
}

// 衝突処理
void CKick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用コライダーであれば
	if (self == mpAttackCol)
	{
		// キャラのポインタに変換
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// 相手のコライダーの持ち主がキャラであれば
		if (chara != nullptr)
		{
			// すでに攻撃済みのキャラでなければ
			if (!IsAttackHitObj(chara))
			{
				//　ダメージを与える
				chara->TakeDamage(1);

				// 攻撃済みリストに追加
				AddAttackHitObj(chara);
			}
		}
	}
}

CMatrix CKick::Matrix() const
{
	// 手に持っていないときは、自分自身の行列を返す
	if (mpAttachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// 手に持っているときは、アタッチしている行列を返す
	else
	{
		CMatrix sm;
		sm.Scale(80.0f, 80.0f, 80.0f);

		return sm * (*mpAttachMtx);
	}
}

// 攻撃開始
void CKick::AttackStart()
{
	CWeaponEnemy::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(true);
}

// 攻撃終了
void CKick::AttackEnd()
{
	CWeaponEnemy::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(false);
}