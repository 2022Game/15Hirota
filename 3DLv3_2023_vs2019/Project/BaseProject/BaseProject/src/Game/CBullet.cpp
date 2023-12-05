#include "CBullet.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CEffect.h"

#define BULLET_O "Character\\Bullet1\\Bullet.obj"
#define BULLET_M "Character\\Bullet1\\Bullet.mtl"

// 弾丸の移動速度
#define MOVE_SPEED 100.0f

CModel* CBullet::mpBullet = nullptr;

CBullet::CBullet()
	: mPos (CVector(0.0f, 0.0f, 0.0f))
	, mMoveDistance(0.0f)
{
	mPos = CVector(0.0f, 0.0f, 0.0f);

	if (mpBullet == nullptr)
	{
		// モデルロード
		mpBullet = new CModel();
		mpBullet->Load(BULLET_O, BULLET_M);
	}

	// 弾丸とコライダーのスケールを設定
	float scale = 50.0f;
	Scale(scale, scale, scale);
	float rad = 1.0f / scale;

	// 攻撃判定用のコライダーを作成
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		rad
	);
	// 攻撃判定用の子ラダーと衝突判定を行う
	// レイヤーとタグを設定
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
}

CBullet::~CBullet()
{
	// 弾丸が削除されたら、コライダーも削除
	SAFE_DELETE_ARRAY(mpAttackCol);
}

void CBullet::Update()
{
	CVector currentPos = Position();
	float moveSpeed = MOVE_SPEED * Time::DeltaTime();
	currentPos += VectorZ() * moveSpeed;;
	Position(currentPos);

	// 弾丸の移動距離を加算
	mMoveDistance += moveSpeed;
	// 一定距離移動したら、弾丸を削除
	if (mMoveDistance >= 100.0f)
	{
		Kill();
	}
}


void CBullet::Render()
{
	mpBullet->Render(Matrix());
}

CMatrix CBullet::Matrix() const
{
	// 自分自身の行列を返す
	if (mpAttachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// アタッチしている行列を返す
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
				bullet->TakeDamage(0);

				// 攻撃済みリストに追加
				AddAttackHitObj(bullet);
			}
		}
	}
}

//
//// 攻撃開始
//void CBullet::AttackStart()
//{
//	CEnemyWeapon::AttackStart();
//	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
//	mpAttackCol->SetEnable(true);
//}
//
//// 攻撃終了
//void CBullet::AttackEnd()
//{
//	CEnemyWeapon::AttackEnd();
//	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
//	mpAttackCol->SetEnable(false);
//}