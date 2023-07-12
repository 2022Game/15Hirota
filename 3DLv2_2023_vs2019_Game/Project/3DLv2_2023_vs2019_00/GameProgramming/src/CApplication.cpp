#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CCollisionManager.h"
#include "CBillBoard.h"
#include "CEnemy3.h"
#include "CSceneManager.h"

//クラスのstatic変数
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;
//CCamera CApplication::mCamera;

CUi* CApplication::spUi = nullptr;
CApplication::~CApplication()
{
	delete spUi;	//インスタンスUiの削除
}
CUi* CApplication::Ui()
{
	return spUi;
}

//後で削除する↓

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル
//モデルデータの指定
#define MODEL_OBJ "res\\Hirutya-ru3.obj", "res\\Hirutya-ru3.mtl"
//敵輸送機モデル
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"
//アイテム1のモデル
#define MODEL_ITEM1 "res\\12190_Heart_v1_L3.obj","res\\12190_Heart_v1_L3.mtl"

//エイリアンモデル
#define MODEL_ALIEN "res\\Alien Animal.obj","res\\Alien Animal.mtl"

//背景モデルデータの指定
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"

//芝生
#define MODEL_SIBAFU "res\\20265_Hexagonal_prism_v1.obj","res\\Blank.mtl"

//CTaskManager CApplication::mTaskManager;

//CTaskManager* CApplication::TaskManager()
//{
//	return &mTaskManager;
//}

//CCamera* CApplication::Camera()
//{
//	return &mCamera;
//}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse()
{
	return mModelViewInverse;
}

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//ゲームシーン読み込み
	CSceneManager::Instance()->LoadScene(EScene::eTitle);

	spUi = new CUi();	//UIクラスの生成
}

void CApplication::Update()
{
	//タスクマネージャの更新
	//mTaskManager.Update();
	CTaskManager::Instance()->Update();
	//コリジョンマネージャの衝突処理
	//削除	CCollisionManager::Instance()->Collision();
	CTaskManager::Instance()->Collision();

	////頂点1､頂点2､頂点3,法線データの作成
	//CVector v0, v1, v2, n;
	////法線を上向きで設定する
	//n.Set(0.0f, 1.0f, 0.0f);
	////頂点1の座標を設定する
	//v0.Set(0.0f, 0.0f, 0.5f);
	////頂点2の座標を設定する
	//v1.Set(1.0f, 0.0f, 0.0f);
	////頂点3の座標を設定する
	//v2.Set(0.0f, 0.0f, -0.5f);

	/*if (mInput.Key('J'))
	{
		mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('L'))
	{
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('I'))
	{
		mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('K'))
	{
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('O'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}*/

	//mPlayer.Update();

	//シーンマネージャーの更新　
	CSceneManager::Instance()->Update();


	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//逆行列の取得
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	//mPlayer.Render();

	//mBackGround.Render();

	//タスクリストの削除
	CTaskManager::Instance()->Delete();
	//タスクマネージャの描画
	CTaskManager::Instance()->Render();

	CCollisionManager::Instance()->Render();

	spUi->Render();	//UIの描画

}
