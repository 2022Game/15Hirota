#ifndef CPICOSWORD_H
#define CPICOSWORD_H

#include "CObjectBase.h"
#include "CWeaponEnemy.h"
#include "CColliderLine.h"
#include "CModel.h"

class CPicoChan;

// �s�R�����\�[�h�N���X
class CPicoSword : public CWeaponEnemy
{
public:
	CPicoSword();
	~CPicoSword();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �U���J�n
	void AttackStart() override;

	// �U���I��
	void AttackEnd() override;

	void SetPicoChanInstance(CPicoChan* pPicoChan);

	// ����̍s����擾
	CMatrix Matrix() const override;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// �}�W�b�N�\�[�h�̃��f��
	CModel* mpSword;
	// �U������p�̃R���C�_�[
	CColliderLine* mpAttackCol;

	CPicoChan* mpPicoChan;
};
#endif