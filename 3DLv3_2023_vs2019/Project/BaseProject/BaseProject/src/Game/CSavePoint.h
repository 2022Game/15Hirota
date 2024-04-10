#ifndef CSAVEPOINT_H
#define CSAVEPOINT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CObjectBase.h"

// �Z�[�u�|�C���g�N���X
class CSavePoint : public CObjectBase
{
public:
	CSavePoint(const CVector& pos, const CVector& scale, const CVector& rot);
	~CSavePoint();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ���f���E�f�ފ֘A
	// �Z�[�u�|�C���g���f��
	CModel* mpSavePointModel;
	// �Z�[�u�|�C���g�̃R���C�_�[
	CColliderLine* mpSaveColLine;

};
#endif