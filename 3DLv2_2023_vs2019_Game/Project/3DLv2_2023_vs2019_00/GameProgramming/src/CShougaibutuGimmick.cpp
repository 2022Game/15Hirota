#include "CShougaibutuGimmick.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CVector.h"

//土台
#define MODEL_SIBAFU "res\\Low Poly Mill.obj","res\\Low Poly Mill.mtl"

CShougaibutuGimmick::CShougaibutuGimmick()
{
	//初期処理
	Init();

	//タスクマネージャーに自身を追加
	CTaskManager::Instance()->Add(this);
}

CShougaibutuGimmick::~CShougaibutuGimmick()
{
	//芝生のモデルデータを破棄
	if (mpShougaibutuA != nullptr)
	{
		delete mpShougaibutuA;
	}

	//破棄
	for (int i = 0; i < mShougaibutuAs.size(); i++)
	{
		delete mShougaibutuAs[i];
	}
	//一応リストもクリアしておく
	mShougaibutuAs.clear();

	//タスクマネージャーから自信を取り除く
	CTaskManager::Instance()->Remove(this);
}

void CShougaibutuGimmick::Init()
{
	//芝生の読み込み
	mpShougaibutuA = new CModel();
	mpShougaibutuA->Load(MODEL_SIBAFU);

	//芝生作成
	CreateShougaibutuA(CVector(10.0f, 0.0f, 20.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.5f, 1.5f, 1.5f));
}

void CShougaibutuGimmick::CreateShougaibutuA(CVector& pos, CVector& rot, CVector& scale)
{
	if (mpShougaibutuA == nullptr)return;

	//リストに追加
	CShougaibutuA* sibafu = new CShougaibutuA(mpShougaibutuA, pos, rot, scale);
	mShougaibutuAs.push_back(sibafu);
}

void CShougaibutuGimmick::Update()
{
	//if (プレイヤーがコインに接地したら)
	{
		for (int i = 0; i < mShougaibutuAs.size(); i++)
		{
			CShougaibutuA* sibabu = mShougaibutuAs[i];
			if (sibabu->a == 0)
			{
				sibabu->a = 1;
			}
		}
	}
}