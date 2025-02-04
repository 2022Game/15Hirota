#pragma once

#include "CTexture.h"
#include "CCharacterManager.h"
#include "CGame.h"
#include "CSound.h"
#include "CVector.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CUi.h"
#include "CSikakuGimmick.h"

class CApplication
{
private:
	static CUi* spUi;	//UIクラスのポインタ
	//モデルからコライダを生成
	//CColliderMesh mColliderMesh;

	//三角コライダの作成
	//CColliderTriangle mColliderTriangle;
	//CColliderTriangle mColliderTriangle2;

	//モデルビューの逆行列
	static CMatrix mModelViewInverse;

	//C5モデル
	//CModel mModelC5;

	//エイリアン
	//CModel mModelAlien;

	//アイテム(仮)
	//CModel mModel_Item;

	//static CTaskManager mTaskManager;
	//CPlayer mPlayer;

	//CModel mBackGround; //背景モデル

	//CModel mModel;
	//CModel mModel1;
	//CVector mEye;

	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//ゲームオーバー
	CGame* mpGame;

	static CCharacterManager mCharacterManager;
	//enum class EState
	//{
	//	ESTART,	//ゲーム開始
	//	EPLAY,	//ゲーム中
	//	ECLEAR,	//ゲームクリア
	//	EOVER,	//ゲームオーバー
	//};
	//EState mState;
	//	CCharacter mRectangle;
	//CPlayer* mpPlayer;
	static CTexture mTexture;
	//CEnemy* mpEnemy;
	//	CBullet* mpBullet;
	//CInput mInput;
	//CFont mFont;
	//CMiss* mpMiss;
	//CCharacterのポインタの可変長配列
	//std::vector<CCharacter*> mCharacters;
	//CSikakuGimmick* mpSikakuGimmick;
public:
	~CApplication();
	static CUi* Ui();	//UIクラスのインスタンスを取得
	//モデルビュー行列の取得
	static const CMatrix& ModelViewInverse();
	//static CTaskManager* TaskManager();
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};