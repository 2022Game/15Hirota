#include "CApplication.h"
#include "CRectangle.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMatrix.h"
#include "CBullet.h"
#include "CCollisionManager.h"

//OpenGL
#include "glut.h"

CVector mEye;

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;
CMatrix CApplication::mModelViewInverse;
CUi* CApplication::spUi = nullptr;


//CTaskManager CApplication::mTaskManager;

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��
//#define MODEL_OBJ "res\\obj.obj","res\\obj.mtl" //���f���f�[�^�̎w��
//�w�i���f���f�[�^�̎w��
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"
#define MODEL_F14 "res\\f14.obj","res\\f14.mtl"
//�A���@���f��
#define MODEL_C5 "res\\c5.obj","res\\c5.mtl"

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

const CMatrix& CApplication::ModelViewInverse()
{
	return mModelViewInverse;
}

//CTaskManager* CApplication::TaskManager()
//{
//	return &mTaskManager;
//}

CUi* CApplication::Ui()
{
	return spUi;	//�C���X�^���X�̃|�C���^��Ԃ�
}

CApplication::~CApplication()
{
	delete spUi;	//�C���X�^���XUi�̍폜
}

void CApplication::Start() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
	mModel.Load(MODEL_F14);
	//C5���f���̓ǂݍ���
	mModelC5.Load(MODEL_C5);
	mBackGround.Load(MODEL_BACKGROUND);
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	CMatrix matrix;
	matrix.Print();
	//mCharacter.Model(&mModel);
	//mCharacter.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));

	//�G�@�̃C���X�^���X�쐬
	new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy3(CVector(-5.0f, 1.0f, -10.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy3(CVector(5.0f, 1.0f, -10.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

	//�r���{�[�h�̍쐬
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);

	spUi = new CUi();	//Ui�N���X�̐���

	//���R���C�_�̊m�F
	/*mColliderTriangle.Set(nullptr, nullptr
		, CVector(-50.0f, 0.0f, -50.0f)
		, CVector(-50.0f, 0.0f, 50.0f)
		, CVector(50.0f, 0.0f, -50.0f));

	mColliderTriangle2.Set(nullptr, nullptr
		, CVector(-50.0f, 0.0f, 50.0f)
		, CVector(50.0f, 0.0f, 50.0f)
		, CVector(50.0f, 0.0f, -50.0f));*/
}

void CApplication::Update()
{
	//�^�X�N�}�l�[�W���̍X�V
	CTaskManager::Instance()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	/*CCollisionManager::Instance()->Collision();*/
	CTaskManager::Instance()->Collision();

	//���_1�A���_2�A���_3�A�@���f�[�^�̍쐬
	CVector v0, v1, v2, n;
	//�@����������Őݒ肷��
	n.Set(0.0f, 1.0f, 0.0f);
	//���_�P�̍��W��ݒ肷��
	v0.Set(0.0f, 0.0f, 0.5f);
	//���_�Q�̍��W�������Ă���
	v1.Set(1.0f, 0.0f, 0.0f);
	//���_�R�̍��W��ݒ肷��
	v2.Set(0.0f, 0.0f, -0.5f);

	if (mInput.Key('J'))
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
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}

	//���_�̐ݒ�
	//gluLookAt(���_X,���_Y,���_Z,���SX,���SY,���SZ,���X,���Y,���Z)
	//gluLookAt(mEye.X(),mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);

	//mModel.Render(CMatrix().Scale(0.1f,0.1f,0.1f));
	//mModel.Render(CMatrix().RotateY(90.0f));
	//mModel.Render(CMatrix().RotateY(90.0f));
	//CMatrix matrix, position, rotation, scale;
	//position.Translate(0.5f, 1.8f, 0.5f);//�ړ��s��ݒ�
	//rotation.RotateY(180.0f);//��]�s��ݒ�
	//scale.Scale(0.1f, 0.1f, 0.1f);//�g��k���s��ݒ�
	//matrix = scale * rotation * position;//�����s��ݒ�
	//mModel.Render(matrix);//���f���̕`��

	//mCharacter.Update();
	//mCharacter.Render();
	
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = mPlayer.Position() + CVector(-0.2f, 1.0f, -3.0f) * mPlayer.MatrixRotate();
	//e = mPlayer.Position() + CVector(0, 1, -3) * mPlayer.MatrixRotate();
	//�����_�����߂�
	c = mPlayer.Position();
	//����������߂�
	u = CVector(0, 1, 0) * mPlayer.MatrixRotate();
	//�J�����̐ݒ�
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//�t�s��̎擾 dd?
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	//mPlayer.Update();
	//mPlayer.Render();

	//�^�X�N���X�g�̍폜
	CTaskManager::Instance()->Delete();

	mBackGround.Render();

	//�^�X�N�}�l�[�W���[�̕`��
	CTaskManager::Instance()->Render();

	CCollisionManager::Instance()->Render();

	spUi->Render();	//UI�̕`��
}