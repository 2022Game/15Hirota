#include "CBillBoard.h"
//#include "CApplication.h"
#include "CCamera.h"

CBillBoard::CBillBoard(ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CObjectBase(tag, prio, sortOrder, pause)
{
}

void CBillBoard::SetSize(const CVector2& size)
{
	mT[0].Vertex
	(
		CVector(size.X(), size.Y(), 0.0f),
		CVector(-size.X(), -size.Y(), 0.0f),
		CVector(size.X(), -size.Y(), 0.0f)
	);
	mT[1].Vertex
	(
		CVector(-size.X(), size.Y(), 0.0f),
		CVector(-size.X(), -size.Y(), 0.0f),
		CVector(size.X(), size.Y(), 0.0f)
	);
	//�@����Z������
	mT[0].Normal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].Normal(CVector(0.0f, 0.0f, 1.0f));
}

void CBillBoard::SetColor(const CColor& color)
{
	//�F�𔒐F��ݒ�
	mMaterial.Diffuse()[0] = color.R();
	mMaterial.Diffuse()[1] = color.G();
	mMaterial.Diffuse()[2] = color.B();
	mMaterial.Diffuse()[3] = color.A();
}

void CBillBoard::Update()
{
}

void CBillBoard::Render()
{
	Render(&mMaterial);
}

//Render(�}�e���A���̃|�C���^)
void CBillBoard::Render(CMaterial* mpMaterial)
{
	//�s��̕ۑ�
	glPushMatrix();

	//��ɃJ�����̕�������������
	CCamera* cam = CCamera::CurrentCamera();
	CMatrix m = cam->GetViewMatrix().Inverse();
	m.Position(CVector::zero);
	glMultMatrixf((m * Matrix()).M());

	//���C�g�I�t
	glDisable(GL_LIGHTING);
	//�`��F�̐ݒ�
	glColor4fv(mpMaterial->Diffuse());
	//�}�e���A���K�p
	mpMaterial->Enabled(CColor::white);
	//�O�p�`�̕`��
	mT[0].Render();
	mT[1].Render();
	//�}�e���A������
	mpMaterial->Disabled();
	//���C�g�I��
	glEnable(GL_LIGHTING);

	//�s���߂�
	glPopMatrix();
}
