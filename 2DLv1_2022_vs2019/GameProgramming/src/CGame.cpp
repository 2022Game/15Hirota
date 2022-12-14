#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer2.h"
#include "CEnemy2.h"
#include "CEnemy3.h"
#include "CPoint.h"
#include "CCamera.h"
#include "main.h"
#include "CDokan.h"
#include "CBlock2.h"
#include "CBlock3.h"
#include "CBlock4.h"
#include "BackGround.h"
#include "CGoal.h"
#include "CCharacter.h"
#include "CKinoko.h"
#include "CMoveBlock.h"

void CGame::Start()
{
	CameraSet();
	//ゲームの描画
	CApplication::CharacterManager()->Render();
	CCamera::End();
	//UI処理
	mpUi->Hp(CPlayer2::Hp());
	mpUi->Enemy(CEnemy2::Num());
	mpUi->Enemy(CEnemy3::Num());
	mpUi->Score(CEnemy2::Score()+CEnemy3::Score());
	mpUi->Render();
	mpUi->Start();
}

bool CGame::IsOver()
{	//HPが0以下か判定結果を戻す
	return CPlayer2::Hp() <= 0;
}

void CGame::Over()
{
	CameraSet();
	//ゲームの描画
	CApplication::CharacterManager()->Render();
	CCamera::End();
	//UI処理
	mpUi->Hp(CPlayer2::Hp());
	mpUi->Enemy(CEnemy2::Num()+ CEnemy3::Num());
	mpUi->Score(CEnemy2::Score() + CEnemy3::Score());
	mpUi->Render();
	mpUi->Over();
}

CGame::~CGame()
{
	//全てのインスタンス削除
	CApplication::CharacterManager()->AllDelete();
	//UIを生成している時
	if (mpUi != nullptr)
	{	//UIを削除し、初期化
		delete mpUi;
		mpUi = nullptr;
	}
}

bool CGame::IsClear()
{
	return CPlayer2::Goal1() <= 0;
	//return CPlayer2::Instance()->sGoal1<= 0;
}

void CGame::Clear()
{
	CameraSet();
	//ゲームの描画
	CApplication::CharacterManager()->Render();
	CCamera::End();
	//UI処理
	mpUi->Hp(CPlayer2::Hp());
	mpUi->Enemy(CEnemy2::Num() + CEnemy3::Num());
	mpUi->Score(CEnemy2::Score() + CEnemy3::Score());
	mpUi->Render();
	mpUi->Clear();
}


CGame::CGame()
	: mpUi(nullptr)
	, mTime(0)
	, mCdx(0)
	, mCdy(0)
	, mScore(0)
{
	CEnemy2::Num(0);
	CEnemy3::Num(0);
	CEnemy2::Score(0);
	CEnemy3::Score(0);
	mpUi = new CUi();
	//テクスチャの入力
	CApplication::Texture()->Load(TEXTURE);
	CApplication::Texture2()->Load(TEXTURE_D);
	CApplication::Texture3()->Load(TEXTURE_B1);
	CApplication::Texture3()->Load(TEXTURE_B2);
	CApplication::Texture3()->Load(TEXTURE_B3);
	CApplication::Texture4()->Load(TEXTURE_E1);
	CApplication::Texture4()->Load(TEXTURE_GOAL);
	CApplication::Texture4()->Load(TEXTURE_KINOKO);
	CApplication::Texture4()->Load(TEXTURE_MoveBlock);
	CApplication::Texture5()->Load(TEXTURE_BACK);
	

	//定数の定義
	const int ROWS = 12; //行数
	const int COLS = 102; //列数
	//2次元配列のマップ
	int map[ROWS][COLS] =
	{ 
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,4,0,3,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,7,7,8,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,2,0,0,0,4,0,9,0,4,6,0,0,0,3,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,11,11,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
	};

	//背景を生成して、キャラクタマネージャに追加
	CApplication::CharacterManager()->Add(
		new CBackground2(3000 * 2,
			3000 * 2,
			3000 * 6, 3000 * 6, CApplication::Texture4()));
	
	//マップの作成
	//行数分繰り返し
	for (int row = 0; row < ROWS; row++)
	{
		//列数分繰り返し
		for (int col = 0; col < COLS; col++)
			
		{
			//1の時、ブロック生成
			if (map[row][col] == 1)
			{
				//ブロックを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CBlock(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
			//2の時、プレイヤー生成
			if (map[row][col] == 2)
			{
				//カメラ用差分
				mCdx = WINDOW_WIDTH / 1.5 - (TIPSIZE + TIPSIZE * 1 * col);
				mCdy = WINDOW_HEIGHT / -3.69 - (TIPSIZE + TIPSIZE * 0 * row);
				//プレイヤーを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					mpPlayer = new CPlayer2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
			//3の時、敵生成
			if (map[row][col] == 3)
			{
				//敵を生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CEnemy2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE, CApplication::Texture()));
			}
			//4の時、折り返しポイント作成
			if (map[row][col] == 4)
			{
				//折り返しポイントを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CPoint(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE, CCharacter::ETag::ETURN));
			}
			//5の時、土管生成
			if (map[row][col] == 5)
			{
				//土管を生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CDokan(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_D, CApplication::Texture2()));
			}
			//6の時、足場ブロックを生成
			if (map[row][col] == 6)
			{
				//足場を生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CBlock2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_B1, CApplication::Texture3()));
			}
			//7の時、上空ブロックを生成
			if (map[row][col] == 7)
			{
				//上空ブロックを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CBlock3(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_B2, CApplication::Texture3()));
			}
			//8の時、ハテナブロックを生成
			if (map[row][col] == 8)
			{
				//ハテナブロックを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CBlock4(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_B2, CApplication::Texture3()));
			}
			//9の時、敵2を生成
			if (map[row][col] == 9)
			{
				//敵2を生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CEnemy3(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_E1, CApplication::Texture4()));
			}
			//10の時、ゴールを生成
			if (map[row][col] == 10)
			{
				//ゴールを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CGoal(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -0.6 * row,
						TIPSIZE, TIPSIZE_GOAL, CApplication::Texture4()));
			}
			//11の時、落下死作成
			if (map[row][col] == 11)
			{
				//折り返しポイントを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CFalling(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE, CCharacter::ETag::EFALLING));
			}
			//12の時、キノコを生成
			if (map[row][col] == 12)
			{
				//キノコを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CKinoko(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_KINOKO, CApplication::Texture4()));
			}
			//13の時、移動ブロックを生成
			if (map[row][col] == 13)
			{
				//移動ブロックを生成して、キャラクタマネージャに追加
				CApplication::CharacterManager()->Add(
					new CMoveBlock(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * -2 * row,
						TIPSIZE, TIPSIZE_MoveBlock, CApplication::Texture4()));
			}

		}
	}
}

void CGame::Update()
{
	//更新、衝突、削除、描画
	CApplication::CharacterManager()->Update();
	CApplication::CharacterManager()->Collision();
	CApplication::CharacterManager()->Delete();
	CameraSet();
	CApplication::CharacterManager()->Render();
	CCamera::End();
	//UI
	mpUi->Time(mTime++);
	mpUi->Score(CEnemy2::Score() + CEnemy3::Score());
	mpUi->Hp(CPlayer2::Hp());
	mpUi->Enemy(CEnemy2::Num() + CEnemy3::Num());
	mpUi->Render();
}

void CGame::CameraSet()
{
	float x = mpPlayer->X() + mCdx;
	float y =  mCdy;
	//float y = mpPlayer->Y() + mCdy;
	CCamera::Start(x - WINDOW_WIDTH / 0.9 
		, x + WINDOW_WIDTH / 0.9
		, y - WINDOW_HEIGHT / 1
		, y + WINDOW_HEIGHT / 1
	);
}
