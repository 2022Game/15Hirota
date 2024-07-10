#ifndef CSTUFFEDROLLSCENE_H
#define CSTUFFEDROLLSCENE_H

#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
#include "CImage.h"

class CSound;
class CTitleMenu;
class CStuffedRoll;

//�^�C�g���V�[��
class CStuffedRollScene : public CSceneBase
{
public:
	//�R���X�g���N�^
	CStuffedRollScene();
	//�f�X�g���N�^
	~CStuffedRollScene();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();

private:
	// �X�^�b�t���[���N���X
	CStuffedRoll* mpStuffedRoll;
};
#endif