#ifndef CCIRCLEEFFECT_H
#define CCIRCLEEFFECT_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CWeapon.h"

// �T�[�N����̃G�t�F�N�g
class CCircleEffect : public CWeapon
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="angle"></param>
	/// <param name="dist"></param>
	CCircleEffect(float angle, float dist);
	~CCircleEffect();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
private:
	// �G�t�F�N�g�̃��f��
	CModel* mpModel;
	// �o�ߎ��Ԋϑ��p
	float mElapsedTime;
	float mAngle;
	float mDistance;
};
#endif