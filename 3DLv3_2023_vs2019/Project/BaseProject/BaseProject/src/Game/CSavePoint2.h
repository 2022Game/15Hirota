#ifndef CSAVEPOINT2_H
#define CSAVEPOINT2_H

#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CObjectBase.h"
class CModel;

// �Z�[�u�|�C���g�N���X
class CSavePoint2 : public CObjectBase
{
public:
	CSavePoint2(const CVector& pos, const CVector& scale, const CVector& rot);
	~CSavePoint2();

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