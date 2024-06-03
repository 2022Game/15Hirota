#pragma once
#include <initializer_list>

// オブジェクト識別用のタグ
enum class ETag
{
	eNone = -1,

	eBullet,			// 弾丸
	eFlame,				// 炎
	eSlash,				// 斬撃
	eBiribiri,			// ビリビリ

	eField,				// フィールドを構成するオブジェクト
	eStageMenuObject,	// ステージメニューのオブジェクト
	eButton,			// ステージ選択ボタン
	eObstacle,			// 障害物
	eRideableObject,	// 乗ることができるオブジェクト
	eItemRecover,		// 回復アイテムのオブジェクト
	eItemInvincible,	// 無敵アイテム
	eAttackObject,		// 攻撃力アップモデル
	eMedal,				// メダルアイテム
	eGoalObject,		// クリア条件のオブジェクト
	eSavePoint,			// セーブポイント
	eJumpingObject,		// ジャンプするオブジェクト
	eNeedleObject,		// 針オブジェクト
	eFall,				// 落下判定用オブジェクト
	eRingBeam,			// リングビームオブジェクト

	ePlayer,			// プレイヤー
	eEnemy,				// エネミー
	eSoldier,

	eWeapon,			// プレイヤーの武器
	eEnemyWeapon,		// 敵の武器

	eBakuhatu,
	eGauge,
	eEnemyFrame,

	eEffect,	// エフェクト
	eBillboard,	// ビルボードイメージ

	eCamera,			// カメラ
	
	Num
};
// オブジェクト識別用のタグの初期化リスト
using Tags = std::initializer_list<ETag>;
