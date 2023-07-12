#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CCollisionManager.h"
#include "CBillBoard.h"
#include "CEnemy3.h"
#include "CSceneManager.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;
//CCamera CApplication::mCamera;

CUi* CApplication::spUi = nullptr;
CApplication::~CApplication()
{
	delete spUi;	//�C���X�^���XUi�̍폜
}
CUi* CApplication::Ui()
{
	return spUi;
}

//��ō폜���遫

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��
//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\Hirutya-ru3.obj", "res\\Hirutya-ru3.mtl"
//�G�A���@���f��
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"
//�A�C�e��1�̃��f��
#define MODEL_ITEM1 "res\\12190_Heart_v1_L3.obj","res\\12190_Heart_v1_L3.mtl"

//�G�C���A�����f��
#define MODEL_ALIEN "res\\Alien Animal.obj","res\\Alien Animal.mtl"

//�w�i���f���f�[�^�̎w��
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"

//�Ő�
#define MODEL_SIBAFU "res\\20265_Hexagonal_prism_v1.obj","res\\Blank.mtl"

//CTaskManager CApplication::mTaskManager;

//CTaskManager* CApplication::TaskManager()
//{
//	return &mTaskManager;
//}

//CCamera* CApplication::Camera()
//{
//	return &mCamera;
//}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse()
{
	return mModelViewInverse;
}

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//�Q�[���V�[���ǂݍ���
	CSceneManager::Instance()->LoadScene(EScene::eTitle);

	spUi = new CUi();	//UI�N���X�̐���
}

void CApplication::Update()
{
	//�^�X�N�}�l�[�W���̍X�V
	//mTaskManager.Update();
	CTaskManager::Instance()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	//�폜	CCollisionManager::Instance()->Collision();
	CTaskManager::Instance()->Collision();

	////���_1����_2����_3,�@���f�[�^�̍쐬
	//CVector v0, v1, v2, n;
	////�@����������Őݒ肷��
	//n.Set(0.0f, 1.0f, 0.0f);
	////���_1�̍��W��ݒ肷��
	//v0.Set(0.0f, 0.0f, 0.5f);
	////���_2�̍��W��ݒ肷��
	//v1.Set(1.0f, 0.0f, 0.0f);
	////���_3�̍��W��ݒ肷��
	//v2.Set(0.0f, 0.0f, -0.5f);

	/*if (mInput.Key('J'))
	{
		mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('L'))
	{
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('I'))
	{
		mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('K'))
	{
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('O'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}*/

	//mPlayer.Update();

	//�V�[���}�l�[�W���[�̍X�V�@
	CSceneManager::Instance()->Update();


	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//�t�s��̎擾
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	//mPlayer.Render();

	//mBackGround.Render();

	//�^�X�N���X�g�̍폜
	CTaskManager::Instance()->Delete();
	//�^�X�N�}�l�[�W���̕`��
	CTaskManager::Instance()->Render();

	CCollisionManager::Instance()->Render();

	spUi->Render();	//UI�̕`��

}
