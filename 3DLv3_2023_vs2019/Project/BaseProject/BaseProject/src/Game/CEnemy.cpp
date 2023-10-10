#include "CEnemy.h"
#include "CEffect.h"
#include "CCollisionManager.h"

//�G1�̃��f��
#define MODEL_Enemy "Character\\Player\\Squid.Model.x"

// �R���X�g���N�^
CEnemy::CEnemy()
	: CCharaBase(ETag::eEnemy, ETaskPriority::eDefault)
{
	// ���f���f�[�^�ǂݍ���
	CModelX* model = new CModelX();
	model->Load(MODEL_Enemy);
}

//�X�V����
void CEnemy::Update()
{
}

void CEnemy::Render()
{
	CCharaBase::Render();
}
