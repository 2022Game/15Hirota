#include "CMajicSword.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

#define SWORD_O "Character\\MajicSword\\MajicSword.obj"
#define SWORD_M "Character\\MajicSword\\MajicSword.mtl"

CMajicSword::CMajicSword()
{
	// モデルロード
	mpSword = new CModel();
	mpSword->Load(SWORD_O, SWORD_M);

	// 攻撃判定用のコライダーを作成
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 1.0f, 1.0f)
	);
	// 攻撃判定用のコライダーと衝突判定を行う
	// レイヤーとタグを設定
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// 最初は攻撃判定用のコライダーをオフにしておく
	mpAttackCol->SetEnable(false);
}

CMajicSword::~CMajicSword()
{

}

void CMajicSword::Update()
{

}

void CMajicSword::Render()
{
	mpSword->Render(Matrix());
}

// 衝突処理
void CMajicSword::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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

CMatrix CMajicSword::Matrix() const
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
		sm.Scale(100.0f, 100.0f, 100.0f);
		return sm * (*mpAttachMtx);
	}
}

// 攻撃開始
void CMajicSword::AttackStart()
{
	CEnemyWeapon::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(true);
}

// 攻撃終了
void CMajicSword::AttackEnd()
{
	CEnemyWeapon::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(false);
}