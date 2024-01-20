//#include "CNumberFloor1.h"
//#include "Maths.h"
//
//// 消えるのにかかる時間
//#define FADE_TIME 3.0f
//// 消えた後の待ち時間
//#define WAIT_TIME 3.0f
//
//// コンストラクタ
//CNumberFloor1::CNumberFloor1(const CVector& pos, const CVector& scale,
//	ETag reactionTag, ELayer reactionLayer)
//	:CRideableObject(ETaskPriority::eNumberFalling)
//	, mState(EState::Idle)
//	, mStateStep(0)
//	, mNumberStep(0)
//	, mReactionTag(reactionTag)
//	, mReactionLayer(reactionLayer)
//	, mFadeTime(0.0f)
//	, mWaitTime(0.0f)
//{
//	// 回数で落ちる床(3回)のモデル取得
//	mpModel = CResourceManager::Get<CModel>("Number3");
//
//	// 回数で落ちる床(3回)のコライダー作成
//	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
//	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
//	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
//
//	// 生成時に設定された触れた時に反応するオブジェクトタグと
//	// コライダーのレイヤーを個別に設定
//	mpColliderMesh->SetCollisionTag(mReactionTag, true);
//	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
//
//	Position(pos);
//	Scale(scale);
//
//}
//
//// デストラクタ
//CNumberFloor1::~CNumberFloor1()
//{
//	SAFE_DELETE(mpColliderMesh);
//}