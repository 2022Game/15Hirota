#pragma once
#include "CTexture.h"
#include "CCharacter3.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include <vector>
#include "CSound.h"

#include "CVector.h"
#include "CModel.h"
#include "CModelX.h"

#include "CTaskManager.h"

#include "CColliderTriangle.h"

#include "CColliderMesh.h"

#include "CUi.h"

#include "CModelX.h"

#include "CXCharacter.h"

#include "CXPlayer.h"

#include "CXEnemy.h"

class CApplication
{
private:
	static CUi* spUi;	//UI�N���X�̃|�C���^
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;

	//�O�p�R���C�_�̍쐬
	//CColliderTriangle mColliderTriangle;
	//CColliderTriangle mColliderTriangle2;

	//���f���r���[�̋t�s��
	static CMatrix mModelViewInverse;

	//C5���f��
	CModel mModelC5;

	//static CTaskManager mTaskManager;
	CPlayer mPlayer;

	CModel mBackGround; //�w�i���f��
	CModel mModel;
	CVector mEye;

	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//�Q�[���I�[�o�[
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	EState mState;
//	CCharacter mRectangle;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CEnemy* mpEnemy;
//	CBullet* mpBullet;
	CInput mInput;
	CFont mFont;
	CModelX mModelX;
	//CCharacter�̃|�C���^�̉ϒ��z��
//	std::vector<CCharacter*> mCharacters;
	CMatrix mMatrix;	//3D�ۑ�8
	//�L�����N�^�N���X�̃C���X�^���X
	//CXCharacter mCharacter;
	//�L�����N�^�N���X�̃C���X�^���X
	CXPlayer mXPlayer;
	//�G�̃C���X�^���X
	CXEnemy mXEnemy;
	//�i�C�g�̃C���X�^���X
	CModelX mKnight;
	
public:
	~CApplication();
	static CUi* Ui();	//UI�N���X�̃C���X�^���X���擾
	//���f���r���[�s��̎擾
	static const CMatrix& ModelViewInverse();
	static CTexture* Texture();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};