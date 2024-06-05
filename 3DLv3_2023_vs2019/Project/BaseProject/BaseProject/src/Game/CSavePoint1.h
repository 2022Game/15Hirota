#ifndef CSAVEPOINT1_H
#define CSAVEPOINT1_H

#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CObjectBase.h"
class CModel;

// �Z�[�u�|�C���g�N���X
class CSavePoint1 : public CObjectBase
{
public:
	CSavePoint1(const CVector& pos, const CVector& scale, const CVector& rot);
	~CSavePoint1();

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