#include "CEnemy.h"
#include "CEffect.h"
#include "CCollisionManager.h"

//敵1のモデル
#define MODEL_Enemy "Character\\Player\\Squid.Model.x"

// コンストラクタ
CEnemy::CEnemy()
	: CCharaBase(ETag::eEnemy, ETaskPriority::eDefault)
{
	// モデルデータ読み込み
	CModelX* model = new CModelX();
	model->Load(MODEL_Enemy);
}

//更新処理
void CEnemy::Update()
{
}

void CEnemy::Render()
{
	CCharaBase::Render();
}
