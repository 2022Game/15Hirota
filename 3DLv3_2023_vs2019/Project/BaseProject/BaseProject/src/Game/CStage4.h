#ifndef CSTAGE4_H
#define CSTAGE4_H

#include "CStageBase.h"

class CSeesawAdventure;
class CStageSky;
class CSeesawAdventure;
class CSeesawStageFallCol;

// �X�e�[�W4�u�V�[�\�[�A�h�x���`���[�v
class CStage4 : public CStageBase
{
public:
	// �R���X�g���N�^
	CStage4();
	// �f�X�g���N�^
	~CStage4();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;

private:
	CSeesawStageFallCol* mpFallCol;
	CStageSky* mpSky;
	CSeesawAdventure* mpFeild;
};
#endif