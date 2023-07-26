#ifndef CTITLESCENE_H
#define CTITLESCENE_H

#include "CSceneBase.h"
#include "CImage.h"
#include "CInput.h"

//�^�C�g���V�[��
class CTitleScene :public CSceneBase
{
public:
	//�R���X�g���N�^
	CTitleScene();
	//�f�X�g���N�^
	~CTitleScene();

	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();
private:
	CInput mInput;	//���͔���p
	CImage* mBgImage;//�w�i�摜
	CImage* mBgImage1;
};
#endif
