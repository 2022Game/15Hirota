//武器クラスのインクルード
#include "CWeapon.h"
#include "CApplication.h"
#include "CCollisionManager.h"

#define ROTATION_YV	CVector(0.0f, 1.0f, 0.0f) //回転速度
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //移動速度
#define ROTATION_XV	CVector(1.0f, 0.0f, 0.0f) //回転速度

CWeapon::CWeapon()
	: mAttackCollider
	(
		this,		//親のポインタ
		&mMatrix,	//親の行列
		CVector(0.0f, 3.0f, 0.3f),	//線分の始点
		CVector(0.0f, 3.0f, -0.3f)	//線分の終点
	)
{
	mpModel = new CModel();
	mpModel->Load("res\\武器.obj", "res\\武器.mtl");
}

//CWeapon(位置, 回転, スケール)
CWeapon::CWeapon(const CVector& pos, const CVector& rot, const CVector& scale, const CVector& vel)
	: CWeapon()
{
	CTransform::Update(pos, rot, scale,vel); //行列の更新
}

//衝突判定の更新処理
void CWeapon::Collision()
{
	//コライダの優先度変更
	mAttackCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision
	(
		&mAttackCollider,
		COLLISIONRANGE
	);
}

//衝突判定
void CWeapon::Collision(CCollider* m, CCollider* o)
{
}

//更新処理
void CWeapon::Update()
{
	//変換行列の更新
	CTransform::Update();
}