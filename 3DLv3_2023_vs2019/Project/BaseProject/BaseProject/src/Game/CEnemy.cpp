#include "CEnemy.h"
#include "CEffect.h"
#include "CCollisionManager.h"
#include "CPicoChan.h"

//�G1�̃��f��
//#define MODEL_Enemy "Character\\Player\\Maria.Model.x"

// �R���X�g���N�^
CEnemy::CEnemy()
	: CCharaBase(ETag::eEnemy, ETaskPriority::eDefault)
{
	//// ���f���f�[�^�ǂݍ���
	//CModelX* model = new CModelX();
	//model->Load();
}

//�X�V����
void CEnemy::Update()
{
}