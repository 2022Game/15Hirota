#include "CWeapon.h"

CWeapon::CWeapon()
	:CObjectBase(ETag::eWeapon, ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{
}

CWeapon::~CWeapon()
{

}

void CWeapon::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

CCharaBase* CWeapon::GetOwner() const
{
	return mOwner;
}

void CWeapon::AttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// 追従する行列を取得
const CMatrix* CWeapon::GetAttachMtx() const
{
	if (mpAttachMtx == nullptr) return nullptr;
	return &mAttachCurrentMtx;
}

// 追従する行列の値を更新
void CWeapon::UpdateAttachMtx()
{
	if (mpAttachMtx == nullptr) return;
	// 現在の行列の状態をメンバ変数の行列へコピー
	mAttachCurrentMtx = *mpAttachMtx;
}

// 攻撃開始
void CWeapon::AttackStart()
{
	mAttackHitObjects.clear();
}

// 攻撃終了
void CWeapon::AttackEnd()
{
}

// 攻撃がヒットしたオブジェクトを追加
void CWeapon::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CWeapon::IsAttackHitObj(CObjectBase* obj) const
{
	// 既にリストに追加されているかを確認する
	auto find = std::find
	(
		mAttackHitObjects.begin(),
		mAttackHitObjects.end(),
		obj
	);
	return find != mAttackHitObjects.end();
}