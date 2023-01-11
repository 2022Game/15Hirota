#include "CApplication.h"
#include "CRectangle.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMatrix.h"
#include "CBullet.h"
//OpenGL
#include "glut.h"

CVector mEye;

//クラスのstatic変数
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;
CTaskManager CApplication::mTaskManager;

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル
//#define MODEL_OBJ "res\\obj.obj","res\\obj.mtl" //モデルデータの指定
//背景モデルデータの指定
#define MODEL_BACKGROUND "res//sky.obj","res//sky.mtl"
#define MODEL_F14 "res//f14.obj","res//f14.mtl"

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

CTaskManager* CApplication::TaskManager()
{
	return &mTaskManager;
}

void CApplication::Start() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//モデルファイルの入力
	mModel.Load(MODEL_F14);
	mBackGround.Load(MODEL_BACKGROUND);
	CMatrix matrix;
	matrix.Print();
	//mCharacter.Model(&mModel);
	//mCharacter.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));
}

void CApplication::Update()
{
	mTaskManager.Update();

	//頂点1、頂点2、頂点3、法線データの作成
	CVector v0, v1, v2, n;
	//法線を上向きで設定する
	n.Set(0.0f, 1.0f, 0.0f);
	//頂点１の座標を設定する
	v0.Set(0.0f, 0.0f, 0.5f);
	//頂点２の座標を競ってする
	v1.Set(1.0f, 0.0f, 0.0f);
	//頂点３の座標を設定する
	v2.Set(0.0f, 0.0f, -0.5f);

	if (mInput.Key('J'))
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
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}

	//視点の設定
	//gluLookAt(視点X,視点Y,視点Z,中心X,中心Y,中心Z,上向X,上向Y,上向Z)
	//gluLookAt(mEye.X(),mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);

	//mModel.Render(CMatrix().Scale(0.1f,0.1f,0.1f));
	//mModel.Render(CMatrix().RotateY(90.0f));
	//mModel.Render(CMatrix().RotateY(90.0f));
	//CMatrix matrix, position, rotation, scale;
	//position.Translate(0.5f, 1.8f, 0.5f);//移動行列設定
	//rotation.RotateY(180.0f);//回転行列設定
	//scale.Scale(0.1f, 0.1f, 0.1f);//拡大縮小行列設定
	//matrix = scale * rotation * position;//合成行列設定
	//mModel.Render(matrix);//モデルの描画

	//mCharacter.Update();
	//mCharacter.Render();
	
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = mPlayer.Position() + CVector(0, 1, -3) * mPlayer.MatrixRotate();
	//注視点を求める
	c = mPlayer.Position();
	//上方向を求める
	u = CVector(0, 1, 0) * mPlayer.MatrixRotate();
	//カメラの設定
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

	//mPlayer.Update();
	//mPlayer.Render();

	//タスクリストの削除
	mTaskManager.Delete();
	//タスクマネージャーの描画
	mTaskManager.Render();

	mBackGround.Render();
}
