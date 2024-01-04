#pragma once
#include <initializer_list>

// 衝突判定レイヤー
enum class ELayer
{
	eNone = -1,
	eTest,

	eField,
	eFieldWall,

	eEffect,
	ePlayer,
	eEnemy,

	eVarious,		// 色々コライダー
	eAttackCol,		// 攻撃を与える時のコライダー
	eBulletCol,		// 弾のコライダー
	eKickCol,		// キックコライダー
	eDamageCol,		// ダメージを受ける時のコライダー
	eJumpingCol,	// ジャンプさせるコライダー
	eGoalCol,		// ゴールのコライダー
	eDamageObject,	// ダメージを与えるコライダー
};
// 衝突判定レイヤーの初期化リスト
using Layers = std::initializer_list<ELayer>;
