#include "CMajicSword.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

//#define SWORD_O "Item\\MajicSword\\MajicSword.obj"
//#define SWORD_M "Item\\MajicSword\\MajicSword.mtl"

CMajicSword::CMajicSword()
{
	mpSword = CResourceManager::Get<CModel>("MajicSword");

	// 攻撃判定用のコライダーを作成
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 3.0f)
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
		sm.Scale(80.0f, 80.0f, 80.0f);

		// 90度回転を表す行列を作成
		CMatrix rotateY;
		CMatrix rotateZ;
		CMatrix rotateX;

		rotateY.RotateY(90.0f);		// Y軸周りに90度回転
		//rotateZ.RotateZ(90.0f);		// Z軸周りに90度回転
		rotateX.RotateX(90.0f);		// X軸周り身90度回転


		return sm * rotateY * rotateX * (*mpAttachMtx);
	}
}

// 攻撃開始
void CMajicSword::AttackStart()
{
	CWeapon::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(true);
}

// 攻撃終了
void CMajicSword::AttackEnd()
{
	CWeapon::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(false);
}