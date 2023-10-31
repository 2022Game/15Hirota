#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CObjectBase.h"
#include "CTriangle.h"
#include "CMaterial.h"
#include "CImage.h"

/*
�r���{�[�h�N���X
��ɃJ�����̕��������l�p�`
*/
class CBillBoard : public CObjectBase {
public:
	//�R���X�g���N�^
	CBillBoard();
	//CBillBoard(�ʒu, ��, ����)
	CBillBoard(CVector pos, float w, float h);
	//CBillBoard(�ʒu, ��, ����, �D��x)
	CBillBoard(CVector pos, float w, float h, int priority);
	//�ʒu�Ƒ傫���̐ݒ�
	//Set(�ʒu, ��, ����)
	void Set(CVector pos, float w, float h);
	//�X�V
	void Update();
	//�`��
	void Render();
	void Render(CMaterial* mpMaterial);

	void SetTexture(const CImage& texture);
	const CImage& GetTexture() const;
protected:
	//�O�p�`2��
	CTriangle mT[2];
	//�}�e���A��
	CMaterial mMaterial;
	CImage mTexture; // �r���{�[�h�̃e�N�X�`��
};
#endif
