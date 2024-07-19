#ifndef CTITLESTAGE_H
#define CTITLESTAGE_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�^�C�g���X�e�[�W�v
class CTitleStage : public CObjectBase
{
public:
	// �R���X�g���N�^
	CTitleStage();
	// �f�X�g���N�^
	~CTitleStage();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �X�e�[�W���f��
	CModel* mpStageModel;
	// ���R���C�_�[
	CColliderMesh* mpTitleCol;
};
#endif