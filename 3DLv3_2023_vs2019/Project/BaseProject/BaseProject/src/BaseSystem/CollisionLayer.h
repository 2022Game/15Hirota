#pragma once
#include <initializer_list>

// 衝突判定レイヤー
enum class ELayer
{
	eNone = -1,
	eTest,

	eField,
	eFieldWall,
	eFieldEnemyWall,

	eEffect,
	ePlayer,
	eEnemy,

	eVarious,		// 色々コライダー
	eRecoverCol,	// 回復コライダー
	eInvincbleCol,	// 無敵コライダー
	eAttackCol,		// 攻撃を与える時のコライダー
	eBulletCol,		// 弾のコライダー
	eKickCol,		// キックコライダー
	eDamageCol,		// ダメージを受ける時のコライダー
	eJumpingCol,	// ジャンプさせるコライダー
	eFallingCol,	// 落下ブロックコライダー
	eGoalCol,		// ゴールのコライダー
	eDamageObject,	// ダメージを与えるコライダー
	eBlockCol,// ブロックのコライダー
};
// 衝突判定レイヤーの初期化リスト
using Layers = std::initializer_list<ELayer>;
