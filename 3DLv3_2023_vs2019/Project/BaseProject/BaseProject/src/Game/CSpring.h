#ifndef CSPRING_H
#define CSPRING_H

#include "CSpringObject.h"
#include "CObjectBase.h"

// �o�l(��ƃo�l)
class CSpring : public CSpringObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="modelPath">���f���p�X</param>
	CSpring(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "Spring");
	// �f�X�g���N�^
	virtual ~CSpring();
};

// �o�l��
class CSpringLower : public CObjectBase
{
public:
	CSpringLower(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "SpringLower");
	~CSpringLower();

	void Update() override;
	void Render() override;
private:
	CModel* mpModel;
};

#endif