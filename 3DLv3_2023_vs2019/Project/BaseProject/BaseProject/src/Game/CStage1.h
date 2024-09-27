#ifndef CSTAGE1_H
#define CSTAGE1_H
#include "CStageBase.h"

class CStageTime;
class CStageSky;
class COneShotFloorField;
class COneShotFallCol;

// �X�e�[�W1�u�����V���b�g�E�t���A�v
class CStage1 : public CStageBase
{
public:
	// �R���X�g���N�^
	CStage1();
	// �f�X�g���N�^
	~CStage1();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;

private:
	COneShotFloorField* mpField;
	COneShotFallCol* mpFallCol;
	CStageSky* mpSky;
};
#endif