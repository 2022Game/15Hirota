#include "CGun.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CInput.h"
#include "CEffect.h"

//#define M1GARAND_O "Item\\Gun_M1Garand\\Gun_M1Garand.obj"
//#define M1GARAND_M "Item\\Gun_M1Garand\\Gun_M1Garand.mtl"


CGun::CGun()
{
	// モデルデータ取得
	mpGun = CResourceManager::Get<CModel>("Gun_M1G");

	//// 攻撃判定用のコライダーを作成
	//mpAttackCol = new CColliderLine
	//(
	//	this, ELayer::eAttackCol,
	//	CVector(0.0f, 0.0f, 0.0f),
	//	CVector(0.0f, 1.0f, 1.0f)
	//);
	//// 攻撃判定用のコライダーと衝突判定を行う
	//// レイヤーとタグを設定
	//mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	//mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// 最初は攻撃判定用のコライダーをオフにしておく
	//mpAttackCol->SetEnable(false);
}

CGun::~CGun()
{

}

void CGun::Update()
{

}

void CGun::Render()
{
	mpGun->Render(Matrix());
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

CMatrix CGun::Matrix() const
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
		sm.Scale(190.0f, 190.0f, 190.0f);

		// 回転を表す行列を作成
		CMatrix rotateY;
		CMatrix rotateZ;
		CMatrix rotateX;

		// 移動を表す行列を作成
		CMatrix positionX;
		CMatrix positionZ;
		CMatrix positionY;

		//rotateX.RotateX(30.0f);		// X軸の回転
		rotateY.RotateY(-105.0f);	// Y軸の回転
		rotateZ.RotateZ(-22.5f);		// Z軸の回転

		float xOffset = 5.0f;	// X軸方向のずれを指定
		positionX.Translate(xOffset, 0, 0);
		float yOffset = 17.0f;	// Y軸方向のずれを指定
		positionY.Translate(0, yOffset, 0);
		float zOffset = 8.0f;	// Z軸方向のずれを指定3.5f
		positionZ.Translate(0, 0, zOffset);

		return sm * rotateZ * rotateY * positionX * positionY * positionZ * (*mpAttachMtx);
	}
}

// 攻撃開始
void CGun::AttackStart()
{
	CWeapon::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(true);
}

// 攻撃終了
void CGun::AttackEnd()
{
	CWeapon::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(false);
}