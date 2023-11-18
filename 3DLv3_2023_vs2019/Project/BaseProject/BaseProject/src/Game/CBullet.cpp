#include "CBullet.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

#define BULLET_O "Character\\Bullet1\\Bullet.obj"
#define BULLET_M "Character\\Bullet1\\Bullet.obj"

CBullet::CBullet()
{
	mPos = CVector(0.0f, 0.0f, 0.0f);

	// モデルロード
	mpBullet = new CModel();
	mpBullet->Load(BULLET_O, BULLET_M);

	// 攻撃判定用のコライダーを作成
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		1.0f //後で変更
	);
	// 攻撃判定用の子ラダーと衝突判定を行う
	// レイヤーとタグを設定
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// 最初は攻撃判定用のコライダーをオフにしておく
	mpAttackCol->SetEnable(false);
}

CBullet::~CBullet()
{

}

void CBullet::Update()
{
	CVector currentPos = Position();
	currentPos = mPos + CVector(0.0f,0.0f,1.0f) * Matrix();

	Position(currentPos);
}


void CBullet::Render()
{
	mpBullet->Render(Matrix());
}

CMatrix CBullet::Matrix() const
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
		sm.Scale(150.0f, 150.0f, 150.0f);

		CMatrix moveMatrix;
		moveMatrix.Translate(0.0f, 0.0f, 10.0f);
		return moveMatrix * sm * (*mpAttachMtx);
	}
}

void CBullet::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用コライダーか
	if (self == mpAttackCol)
	{
		// 弾をポインタに変換
		CCharaBase* bullet = dynamic_cast<CCharaBase*>(other->Owner());
		// 相手のコライダーの持ち主が弾であれば
		if (bullet != nullptr)
		{
			// すでに攻撃済みの弾でなければ
			if (!IsAttackHitObj(bullet))
			{
				// ダメージを与える
				bullet->TakeDamage(1);

				// 攻撃済みリストに追加
				AddAttackHitObj(bullet);
			}
		}
	}
}


// 攻撃開始
void CBullet::AttackStart()
{
	CEnemyWeapon::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(true);
}

// 攻撃終了
void CBullet::AttackEnd()
{
	CEnemyWeapon::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(false);
}