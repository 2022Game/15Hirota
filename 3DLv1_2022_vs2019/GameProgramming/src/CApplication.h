#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include "CMiss.h"
#include <vector>
#include "CCharacterManager.h"
#include "CGame.h"
#include "CSound.h"
#include "CModel.h"
#include "CCharacter3.h"
#include "CTaskManager.h"
#include "CBillBoard.h"
#include "CVector.h"
#include "CColliderTriangle.h"
#include "CColliderMesh.h"

class CApplication
{
private:
	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//ゲームオーバー
	CGame* mpGame;
	static CCharacterManager mCharacterManager;
	static CTexture mTexture;
	//モデルビューの逆行列
	static CMatrix mModelViewInverse;
	//static CTaskManager mTaskManager;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
	static CUi* spUi;	//UIクラスのポインタ
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};
	EState mState;
    //CCharacter mRectangle;
	CPlayer* mpPlayer;
	CEnemy* mpEnemy;
    //CBullet* mpBullet;
	CInput mInput;
	CFont mFont;
	CMiss* mpMiss;
	//モデルクラスのインスタンス作成
	CModel mModel;
	//CCharacterのポインタの可変長配列
	CModel mBackGround; //背景モデル
    //std::vector<CCharacter*> mCharacters;
	//CCharacter3 mCharacter;
	CPlayer mPlayer;
	//C5モデル
	CModel mModelC5;
	//△コライダの作成
	/*CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;*/
public:
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();
	static const CMatrix& ModelViewInverse();
	static CUi* Ui();	//Uiクラスのインスタンスを取得
	//static CTaskManager* TaskManager();
	~CApplication();
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};