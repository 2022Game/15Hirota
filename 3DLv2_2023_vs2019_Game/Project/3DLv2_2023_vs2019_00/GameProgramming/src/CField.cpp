#include "CField.h"
#include "CTaskManager.h"

//�R���X�g���N�^
CField::CField()
{
	//�|�[�Y�̎�ނ�ݒ�
	SetPauseType(TaskPauseType::eGame);
	//�^�X�N�̗D��x��ݒ�
	mPriority = (int)TaskPriority::eBackground;

	//�w�i�̃��f���f�[�^�ǂݍ���
	mpModel = new CModel;
	mpModel->Load("res\\sky,obj", "res\\sky.mtl");
	//�ǂݍ��񂾔w�i�̃��f���f�[�^�ŃR���C�_���쐬
	mColliderMesh.Set(this, &mMatrix, mpModel);
}

//�f�X�g���N�^
CField::~CField()
{
	delete mpModel;
	mpModel = nullptr;
}

//�X�V����
void CField::Update()
{
	CTransform::Update();
}