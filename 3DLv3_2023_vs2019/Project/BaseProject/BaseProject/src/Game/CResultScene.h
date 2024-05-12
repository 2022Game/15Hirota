#ifndef CRESULTSCENE_H
#define CRESULTSCENE_H

#include "CSceneBase.h"
#include "CInput.h"
class CImage;
class CResultAnnouncement;

// ���U���g�V�[��
class CResultScene : public CSceneBase
{
public:
	// �R���X�g���N�^
	CResultScene();
	// �f�X�g���N�^
	~CResultScene();

	// �ǂݍ���
	void Load();

	// �X�V����
	void Update();

private:
	CResultAnnouncement* mpResult;
};
#endif