#include "CClearScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CTitleScene.h"
#include "CPlayer.h"

#define CLEAER "UI\\Clear.jpeg"

// コンストラクタ
CClearScene::CClearScene()
	:CSceneBase(EScene::eClear)
{
}

// デストラクタ
CClearScene::~CClearScene()
{
}

// 読み込み
void CClearScene::Load()
{
	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

// 更新処理
void CClearScene::Update()
{
	if (CInput::PushKey('C'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}