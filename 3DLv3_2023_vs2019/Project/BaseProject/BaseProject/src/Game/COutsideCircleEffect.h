#ifndef COUTSIDECIRCLEEFFECT_H
#define COUTSIDECIRCLEEFFECT_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CWeapon.h"

// �T�[�N����̃G�t�F�N�g
class COutsideCircleEffect : public CWeapon
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="angle"></param>
	/// <param name="dist"></param>
	COutsideCircleEffect(float angle, float dist);
	~COutsideCircleEffect();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
private:
	// �G�t�F�N�g�̃��f��
	CModel* mpCircleModel;

	// �o�ߎ��Ԋϑ��p
	float mElapsedTime;
	float mAngle;
	float mDistance;
};
#endif