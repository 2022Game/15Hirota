#ifndef CSIGNBOARD_H
#define CSIGNBOARD_H

#include "CModel.h"
#include "CColliderMesh.h"
#include "CRideableObject.h"
#include "CSignboardUI.h"
class CImage;

class CSignboard : public CRideableObject
{
public:
	//インスタンスのポインタの取得
	static CSignboard* Instance();

	CSignboard(const CVector& position, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CSignboard();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	bool IsFoundPlayer() const;	//プレイヤーを見つけたか

	void Update();
	void Render();

private:
	// プレイヤーのインスタンス
	static CSignboard* spInstance;
	// 表示画像の状態
	enum class EState
	{
		Idle,		// 待機状態
		Appeared,	// 現れている状態
	};
	//// 状態を切り替える
	//void ChangeState(EState state);
	//// 待機状態
	//void UpdateIdle();
	//// 現れている状態
	//void UpdateAppeared();

	CImage* mUkyeText;		// テキストイメージ
	CImage* mPauseText;		// PAUSEテキストのイメージ
	CImage* mText;			// 看板のテキスト画像


	CModel* mpModel;
	CColliderMesh* mpColliderMesh;

	EState mState;
	int mStateStep;
	int mPauseStep;

	ETag mReactionTag;	// 触れた時に反応するオブジェクトのタグ
	ELayer mReactionLayer;	// 触れた時に反応するレイヤー

	
	bool mIsPaused;			//ポーズ中かどうか

	float mElapsedTime;		//経過時間計測用
	float mPauseTextAlpha;	//PAUSEテキストのアルファ値保存用

	CSignboardUI* mpUkye;

};
#endif