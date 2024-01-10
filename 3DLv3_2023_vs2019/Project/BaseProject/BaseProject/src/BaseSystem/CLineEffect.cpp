#include "CLineEffect.h"
#include <glut.h>
#include "Maths.h"

// �R���X�g���N�^
CLineEffect::CLineEffect(ETag tag)
	: CEffect(tag)
	, mpTexture(nullptr)
{
}

// �f�X�g���N�^
CLineEffect::~CLineEffect()
{
}

// �e�N�X�`���ݒ�
void CLineEffect::SetTexture(std::string texName)
{
	mpTexture = CResourceManager::Get<CTexture>(texName);
}

// ���̃|�C���g��ǉ�
int CLineEffect::AddPoint(const CVector& pos, float startWidth, float endWidth)
{
	CLinePoint* point = new CLinePoint(pos, startWidth, endWidth);
	mPoints.push_back(point);
	return mPoints.size() - 1;
}

// ���̃|�C���g���폜
void CLineEffect::RemovePoint(int index)
{
	if (!(0 <= index && index < mPoints.size())) return;
	CLinePoint* point = mPoints[index];
	mPoints[index] = nullptr;
	mPoints.erase(mPoints.begin() + index);
	delete point;
}

// ���̃|�C���g�����擾
int CLineEffect::GetPointCount() const
{
	return mPoints.size();
}

// ���̃|�C���g�̍��W��ݒ�
void CLineEffect::SetPos(int index, const CVector& pos)
{
	if (!(0 <= index && index < mPoints.size())) return;
	mPoints[index]->pos = pos;
}

// ���̃|�C���g�̍��W���擾
CVector CLineEffect::GetPos(int index) const
{
	if (!(0 <= index && index < mPoints.size())) return CVector();
	return mPoints[index]->pos;
}

//// ���̃|�C���g�̕���ݒ�
//void CLineEffect::SetWidth(int index, float width)
//{
//	if (!(0 <= index && index < mPoints.size())) return;
//	mPoints[index]->width = width;
//}
//
//// ���̃|�C���g�̕����擾
//float CLineEffect::GetWidth(int index) const
//{
//	if (!(0 <= index && index < mPoints.size())) return 0.0f;
//	return mPoints[index]->width;
//}

// �X�V
void CLineEffect::Update()
{
}

// �`��
void CLineEffect::Render()
{
	int size = mPoints.size();

	// �|�C���g��2�ȏ�Ȃ��Ȃ�΁A�`�悵�Ȃ�
	if (size < 2) return;

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glColor3f(mColor.R(), mColor.G(), mColor.B());

	// �e�N�X�`�����ݒ肳��Ă�����A�e�N�X�`���𔽉f
	if (mpTexture != nullptr)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, mpTexture->Id());
	}

	for (int i = 0; i < size - 1; i++)
	{
		CLinePoint* start = mPoints[i];
		CLinePoint* end = mPoints[i + 1];
		if (start == nullptr || end == nullptr) continue;
		const CVector& startPos = start->pos;
		const CVector& endPos = end->pos;
		float startWidth = Math::Lerp(start->startWidth, start->endWidth, 1.0f - start->alpha);
		float endWidth = Math::Lerp(end->startWidth, end->endWidth, 1.0f - end->alpha);

		CVector v = endPos - startPos;
		CVector side = CVector::Cross(v.Normalized(), CVector::up);
		CVector up = CVector::Cross(v.Normalized(), side);

		bool prev = i > 0;
		CLinePoint* prevS = prev ? mPoints[i - 1] : nullptr;
		CLinePoint* prevE = prev ? mPoints[i] : nullptr;
		if (prev && prevS == nullptr) prev = false;
		CVector prevV = prev ? prevE->pos - prevS->pos : CVector::zero;
		CVector prevSide = prev ? CVector::Cross(prevV.Normalized(), CVector::up) : CVector::zero;
		CVector prevUp = prev ? CVector::Cross(prevV.Normalized(), prevSide) : CVector::zero;
		bool next = i + 1 < size - 1;
		CLinePoint* nextS = next ? mPoints[i + 1] : nullptr;
		CLinePoint* nextE = next ? mPoints[i + 2] : nullptr;
		CVector nextV = next ? nextE->pos - nextS->pos : CVector::zero;
		CVector nextSide = next ? CVector::Cross(nextV.Normalized(), CVector::up) : CVector::zero;
		CVector nextUp = next ? CVector::Cross(nextV.Normalized(), nextSide) : CVector::zero;

		// �c��`��
		{
			CVector vtx0 = startPos + up * startWidth * 0.5f;
			CVector vtx1 = startPos - up * startWidth * 0.5f;
			if (prev)
			{
				float width = Math::Lerp(prevE->startWidth, prevE->endWidth, 1.0f - prevE->alpha);
				CVector prevVtx0 = prevE->pos + prevUp * width * 0.5f;
				CVector prevVtx1 = prevE->pos - prevUp * width * 0.5f;
				vtx0 = (vtx0 + prevVtx0) * 0.5f;
				vtx1 = (vtx1 + prevVtx1) * 0.5f;
			}

			CVector vtx2 = endPos + up * endWidth * 0.5f;
			CVector vtx3 = endPos - up * endWidth * 0.5f;
			if (next)
			{
				float width = Math::Lerp(nextS->startWidth, nextS->endWidth, 1.0f - nextS->alpha);
				CVector nextVtx0 = nextS->pos + nextUp * width * 0.5f;
				CVector nextVtx1 = nextS->pos - nextUp * width * 0.5f;
				vtx2 = (vtx2 + nextVtx0) * 0.5f;
				vtx3 = (vtx3 + nextVtx1) * 0.5f;
			}

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3fv((const float*)&vtx0);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3fv((const float*)&vtx1);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3fv((const float*)&vtx2);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3fv((const float*)&vtx3);
			glEnd();
		}
		// ����`��
		{
			CVector vtx0 = startPos + side * startWidth * 0.5f;
			CVector vtx1 = startPos - side * startWidth * 0.5f;
			if (prev)
			{
				float width = Math::Lerp(prevE->startWidth, prevE->endWidth, 1.0f - prevE->alpha);
				CVector prevVtx0 = prevE->pos + prevSide * width * 0.5f;
				CVector prevVtx1 = prevE->pos - prevSide * width * 0.5f;
				vtx0 = (vtx0 + prevVtx0) * 0.5f;
				vtx1 = (vtx1 + prevVtx1) * 0.5f;
			}

			CVector vtx2 = endPos + side * endWidth * 0.5f;
			CVector vtx3 = endPos - side * endWidth * 0.5f;
			if (next)
			{
				float width = Math::Lerp(nextS->startWidth, nextS->endWidth, 1.0f - nextS->alpha);
				CVector nextVtx0 = nextS->pos + nextSide * width * 0.5f;
				CVector nextVtx1 = nextS->pos - nextSide * width * 0.5f;
				vtx2 = (vtx2 + nextVtx0) * 0.5f;
				vtx3 = (vtx3 + nextVtx1) * 0.5f;
			}

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3fv((const float*)&vtx0);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3fv((const float*)&vtx1);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3fv((const float*)&vtx2);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3fv((const float*)&vtx3);
			glEnd();
		}
	}

	// �e�N�X�`�����ݒ肳��Ă�����A�e�N�X�`���𖳌���Ԃɖ߂�
	if (mpTexture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}

	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
}