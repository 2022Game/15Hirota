#include "CApplication.h"
#include "CRectangle.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMatrix.h"
#include "CBullet.h"
//OpenGL
#include "glut.h"

CVector mEye;

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;
CTaskManager CApplication::mTaskManager;

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��
//#define MODEL_OBJ "res\\obj.obj","res\\obj.mtl" //���f���f�[�^�̎w��
//�w�i���f���f�[�^�̎w��
#define MODEL_BACKGROUND "res//sky.obj","res//sky.mtl"
#define MODEL_F14 "res//f14.obj","res//f14.mtl"

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

CTaskManager* CApplication::TaskManager()
{
	return &mTaskManager;
}

void CApplication::Start() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
	mModel.Load(MODEL_F14);
	mBackGround.Load(MODEL_BACKGROUND);
	CMatrix matrix;
	matrix.Print();
	//mCharacter.Model(&mModel);
	//mCharacter.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));
}

void CApplication::Update()
{
	mTaskManager.Update();

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
	e = mPlayer.Position() + CVector(0, 1, -3) * mPlayer.MatrixRotate();
	//�����_�����߂�
	c = mPlayer.Position();
	//����������߂�
	u = CVector(0, 1, 0) * mPlayer.MatrixRotate();
	//�J�����̐ݒ�
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

	//mPlayer.Update();
	//mPlayer.Render();

	//�^�X�N���X�g�̍폜
	mTaskManager.Delete();
	//�^�X�N�}�l�[�W���[�̕`��
	mTaskManager.Render();

	mBackGround.Render();
}
