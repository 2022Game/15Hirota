#ifndef CCLEARSCENE_H
#define CCLEARSCENE_H
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
class CImage;

class CClearScene :public CSceneBase
{
public:
	// �R���X�g���N�^
	CClearScene();
	// �f�X�g���N�^
	~CClearScene();

	// �ǂݍ���
	void Load();

	// �X�V����
	void Update();
private:
	CImage* mpClearImage;
};
#endif