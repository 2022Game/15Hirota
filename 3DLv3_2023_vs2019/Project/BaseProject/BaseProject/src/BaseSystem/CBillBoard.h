#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CObjectBase.h"
#include "CTriangle.h"
#include "CMaterial.h"
#include "CColor.h"

/*
�r���{�[�h�N���X
��ɃJ�����̕��������l�p�`
*/
class CBillBoard : public CObjectBase {
public:
	CBillBoard(ETag tag = ETag::eNone,
		ETaskPriority prio = ETaskPriority::eDefault,
		int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eDefault);

	void SetSize(const CVector2& size);
	void SetColor(const CColor& color);
	//�X�V
	void Update() override;
	//�`��
	void Render() override;
	void Render(CMaterial* mpMaterial);

protected:
	//�O�p�`2��
	CTriangle mT[2];
	//�}�e���A��
	CMaterial mMaterial;
};
#endif
