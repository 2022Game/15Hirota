#include "CField.h"
#include "CTaskManager.h"

//コンストラクタ
CField::CField()
{
	//ポーズの種類を設定
	SetPauseType(TaskPauseType::eGame);
	//タスクの優先度を設定
	mPriority = (int)TaskPriority::eBackground;

	//背景のモデルデータ読み込み
	mpModel = new CModel;
	mpModel->Load("res\\sky,obj", "res\\sky.mtl");
	//読み込んだ背景のモデルデータでコライダを作成
	mColliderMesh.Set(this, &mMatrix, mpModel);
}

//デストラクタ
CField::~CField()
{
	delete mpModel;
	mpModel = nullptr;
}

//更新処理
void CField::Update()
{
	CTransform::Update();
}