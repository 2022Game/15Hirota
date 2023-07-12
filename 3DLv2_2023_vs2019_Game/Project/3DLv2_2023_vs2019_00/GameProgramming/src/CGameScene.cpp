#include "CGameScene.h"
#include "CPlayer.h"
#include "CAlien.h"
#include "CSikakuGimmick.h"
#include "CItem1.h"
#include "CEnemy3.h"
#include "CColliderMesh.h"
#include "CField.h"

//�R���X�g���N�^
CGameScene::CGameScene()
	:CSceneBase(EScene::eGame)
{
}

//�f�X�g���N�^
CGameScene::~CGameScene()
{
}

//�V�[���ǂݍ���
void CGameScene::Load()
{
	//�����Ń^�C�g����ʂɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	//�w�i�쐬
	AddTask(new CField());

	//�v���C���[�쐬
	CPlayer* player = new CPlayer();
	player->Scale(CVector(0.25f, 0.25f, 0.25f));
	player->Position(CVector(0.0f, 2.0f, 0.0f));
	player->Rotation(CVector(0.0f, 180.0f, 0.0f));

	//�A�C�e���쐬
	AddTask(new CAlien(CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f)));





	//���f���t�@�C���̓���
	mModel.Load(MODEL_OBJ);		//�v���C���[
	mModel1.Load(MODEL_ITEM1);	//�A�C�e��1
	mBackGround.Load(MODEL_BACKGROUND);
	//CMatrix matrix;
	//matrix.Print();	//�\���m�F�p

	//mEye = CVector(1.0f, 2.0f, 3.0f);

	mPlayer.Model(&mModel);
	

	//ITEM1�̃��f���̓ǂݍ���
	/*mModel_Item.Load(MODEL_ITEM1);
	new CItem1(&mModel_Item, CVector(-50.0f, 0.0f, -10.0f),
		CVector(270.0f, 0.0f, -90.0f), CVector(0.09f, 0.09f, 0.09f));*/


	//C5���f���̓ǂݍ���
	mModelC5.Load(MODEL_C5);
	//�G�@�̃C���X�^���X�쐬
	/*new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelC5, CVector(20.0f, 10.0f, -130.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));*/


	mModelAlien.Load(MODEL_ALIEN);
	new CEnemy3(&mModelAlien, CVector(-50.0f, 0.0f, 2.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy3(&mModelAlien, CVector(-100.0f, 0.0f, -50.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	//�G�C���A�����f���̓ǂݍ���
	/*mModelAlien.Load(MODEL_ALIEN);
	new CEnemy3(&mModelAlien, CVector(100.0f, 0.0f, 0.0f),
		CVector(0.0f,0.0f,0.0f), CVector(0.1f, 0.1f, 0.1f));*/

		//�r���{�[�h�̐���
		//new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);

		////�O�p�R���C�_�̊m�F
		//mColliderTriangle.Set(nullptr, nullptr
		//	, CVector(-50.0f, 0.0f, -50.0f)
		//	, CVector(-50.0f, 0.0f, 50.0f)
		//	, CVector(50.0f, 0.0f, -50.0f));
		//mColliderTriangle2.Set(nullptr, nullptr
		//	, CVector(-50.0f, 0.0f, 50.0f)
		//	, CVector(50.0f, 0.0f, 50.0f)
		//	, CVector(50.0f, 0.0f, -50.0f));

		//�w�i���f������O�p�R���C�_�𐶐�
		//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	//mColliderMesh1.Set(nullptr, nullptr, &mModel_Item);

	/*new CEnemy3(CVector(-5.0f, 1.0f, -10.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy3(CVector(5.0f, 1.0f, -10.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));*/

	//�l�p�M�~�b�N��CSikakuGimmick���ɂ܂Ƃ߂�
	mpSikakuGimmick = new CSikakuGimmick();

}

//�V�[���̍X�V����
void CGameScene::Update()
{
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr)return;

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = player->Position() + CVector(0.2f, 1.5f, -3.5f) * player->MatrixRotate();
	//�����_�����߂�
	c = player->Position();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * player->MatrixRotate();
	//�J�����̐ݒ�
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
}