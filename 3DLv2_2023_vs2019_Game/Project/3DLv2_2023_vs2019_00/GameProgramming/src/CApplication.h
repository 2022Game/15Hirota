#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter3.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include "CMiss.h"
#include <vector>
#include "CCharacterManager.h"

#include "CGame.h"
#include "CSound.h"

#include "CVector.h"
#include "CModel.h"

#include "CTaskManager.h"

#include "CColliderTriangle.h"

#include "CColliderMesh.h"

#include "CUi.h"
#include "CItem1.h"

class CApplication
{
private:
	static CUi* spUi;	//UI�N���X�̃|�C���^
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;
	CColliderMesh mColliderMesh1;

	//�O�p�R���C�_�̍쐬
	//CColliderTriangle mColliderTriangle;
	//CColliderTriangle mColliderTriangle2;

	//���f���r���[�̋t�s��
	static CMatrix mModelViewInverse;

	//C5���f��
	CModel mModelC5;

	//�A�C�e��(��)
	CItem1 mItem1;

	//static CTaskManager mTaskManager;
	CPlayer mPlayer;

	CModel mBackGround; //�w�i���f��
	CModel mModel;
	CModel mModel1;
	CVector mEye;

	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//�Q�[���I�[�o�[
	CGame* mpGame;

	static CCharacterManager mCharacterManager;
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
	CMiss* mpMiss;
	//CCharacter�̃|�C���^�̉ϒ��z��
//	std::vector<CCharacter*> mCharacters;
public:
	~CApplication();
	static CUi* Ui();	//UI�N���X�̃C���X�^���X���擾
	//���f���r���[�s��̎擾
	static const CMatrix& ModelViewInverse();
	//static CTaskManager* TaskManager();
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};