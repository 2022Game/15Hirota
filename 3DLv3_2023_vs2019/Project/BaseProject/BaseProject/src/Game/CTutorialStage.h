#ifndef CTUTORIALSTAGE_H
#define CTUTORIALSTAGE_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// �`���[�g���A���X�e�[�W
class CTutorialStage : public CObjectBase
{
public:
	// �R���X�g���N�^
	CTutorialStage();
	// �f�X�g���N�^
	~CTutorialStage();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	CModel* mpStageModel;
	CColliderMesh* mpFloor;
	CColliderMesh* mpWall;
};
#endif