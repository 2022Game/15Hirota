#pragma once
#include "CEffect.h"
#include "CTexture.h"

class CLinePoint
{
public:
	CVector pos;
	float startWidth;
	float endWidth;
	float elapsed;
	float alpha;
	CLinePoint(const CVector& p, float sw, float ew)
		: pos(p), startWidth(sw), endWidth(ew), elapsed(0.0f), alpha(1.0f) {};
};

// �����G�t�F�N�g
class CLineEffect : public CEffect
{
public:
	// �R���X�g���N�^
	CLineEffect(ETag tag);
	// �f�X�g���N�^
	virtual ~CLineEffect();

	// �e�N�X�`���ݒ�
	void SetTexture(std::string texName);

	// ���̃|�C���g��ǉ�
	int AddPoint(const CVector& pos, float startWidth, float endWidth);
	// ���̃|�C���g���폜
	void RemovePoint(int index);

	// ���̃|�C���g�����擾
	int GetPointCount() const;

	// ���̃|�C���g�̍��W��ݒ�
	void SetPos(int index, const CVector& pos);
	// ���̃|�C���g�̍��W���擾
	CVector GetPos(int index) const;

	//// ���̃|�C���g�̕���ݒ�
	//void SetWidth(int index, float width);
	//// ���̃|�C���g�̕����擾
	//float GetWidth(int index) const;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

protected:
	// ���̃e�N�X�`��
	CTexture* mpTexture;
	// ���̃|�C���g�̃��X�g
	std::vector<CLinePoint*> mPoints;
};