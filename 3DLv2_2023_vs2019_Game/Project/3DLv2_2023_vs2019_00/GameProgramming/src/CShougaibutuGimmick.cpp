#include "CShougaibutuGimmick.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CVector.h"

//�y��
#define MODEL_SIBAFU "res\\Low Poly Mill.obj","res\\Low Poly Mill.mtl"

CShougaibutuGimmick::CShougaibutuGimmick()
{
	//��������
	Init();

	//�^�X�N�}�l�[�W���[�Ɏ��g��ǉ�
	CTaskManager::Instance()->Add(this);
}

CShougaibutuGimmick::~CShougaibutuGimmick()
{
	//�Ő��̃��f���f�[�^��j��
	if (mpShougaibutuA != nullptr)
	{
		delete mpShougaibutuA;
	}

	//�j��
	for (int i = 0; i < mShougaibutuAs.size(); i++)
	{
		delete mShougaibutuAs[i];
	}
	//�ꉞ���X�g���N���A���Ă���
	mShougaibutuAs.clear();

	//�^�X�N�}�l�[�W���[���玩�M����菜��
	CTaskManager::Instance()->Remove(this);
}

void CShougaibutuGimmick::Init()
{
	//�Ő��̓ǂݍ���
	mpShougaibutuA = new CModel();
	mpShougaibutuA->Load(MODEL_SIBAFU);

	//�Ő��쐬
	CreateShougaibutuA(CVector(10.0f, 0.0f, 20.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.5f, 1.5f, 1.5f));
}

void CShougaibutuGimmick::CreateShougaibutuA(CVector& pos, CVector& rot, CVector& scale)
{
	if (mpShougaibutuA == nullptr)return;

	//���X�g�ɒǉ�
	CShougaibutuA* sibafu = new CShougaibutuA(mpShougaibutuA, pos, rot, scale);
	mShougaibutuAs.push_back(sibafu);
}

void CShougaibutuGimmick::Update()
{
	//if (�v���C���[���R�C���ɐڒn������)
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