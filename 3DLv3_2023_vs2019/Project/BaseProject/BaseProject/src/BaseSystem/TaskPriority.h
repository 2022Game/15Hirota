#pragma once

// Taskの優先順序
enum class ETaskPriority
{
	eNone = -1,

	// 3D関連
	eBackground,	// 背景
	eDefault,		// デフォルト
	eEnemyGauge,	// エネミーのゲージ
	eEnemyUi,		// エネミーのUI

	ePlayer,		// プレイヤー
	eEnemy,			// エネミー


	eItem,			// アイテム
	eWeapon,		// プレイヤー武器
	eEnemyWeapon,	// 敵の武器

	eEffect,
	eBillboard,		// ビルボードイメージ
	eMedal,			// メダルオブジェクト
	eTransparent,	// 透明オブジェクト
	eFalling,		// 落下オブジェクト
	eRising,		// 上昇するオブジェクト
	eNumberFalling,	// 回数で落下するオブジェクト
	eHatenaOBJ,		// ハテナブロックオブジェクト
	eNeedle,		// 針オブジェクト
	eRotate,		// 回転するオブジェクト

	eCamera,		// カメラ

	// 2D関連
	eUI,			// UI関連のデフォルト
	eFade,		// 画面フェード
	eSystem,		// システム関連
	eDebug,			// デバッグ関連

	Num,

	// 2D関連のタスクの開始位置
	Start2d = eUI,
};