#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
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
#include "CModel.h"
#include "CCharacter3.h"
#include "CTaskManager.h"

class CApplication
{
private:
	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//�Q�[���I�[�o�[
	CGame* mpGame;
	static CCharacterManager mCharacterManager;
	static CTaskManager mTaskManager;
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	EState mState;
    //CCharacter mRectangle;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CEnemy* mpEnemy;
    //CBullet* mpBullet;
	CInput mInput;
	CFont mFont;
	CMiss* mpMiss;
	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel;
	//CCharacter�̃|�C���^�̉ϒ��z��
	CModel mBackGround; //�w�i���f��
    //std::vector<CCharacter*> mCharacters;
	//CCharacter3 mCharacter;
	CPlayer mPlayer;
public:
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();
	static CTaskManager* TaskManager();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};