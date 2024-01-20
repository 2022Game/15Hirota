//#include "CNumberFloor1.h"
//#include "Maths.h"
//
//// ������̂ɂ����鎞��
//#define FADE_TIME 3.0f
//// ��������̑҂�����
//#define WAIT_TIME 3.0f
//
//// �R���X�g���N�^
//CNumberFloor1::CNumberFloor1(const CVector& pos, const CVector& scale,
//	ETag reactionTag, ELayer reactionLayer)
//	:CRideableObject(ETaskPriority::eNumberFalling)
//	, mState(EState::Idle)
//	, mStateStep(0)
//	, mNumberStep(0)
//	, mReactionTag(reactionTag)
//	, mReactionLayer(reactionLayer)
//	, mFadeTime(0.0f)
//	, mWaitTime(0.0f)
//{
//	// �񐔂ŗ����鏰(3��)�̃��f���擾
//	mpModel = CResourceManager::Get<CModel>("Number3");
//
//	// �񐔂ŗ����鏰(3��)�̃R���C�_�[�쐬
//	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
//	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
//	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
//
//	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
//	// �R���C�_�[�̃��C���[���ʂɐݒ�
//	mpColliderMesh->SetCollisionTag(mReactionTag, true);
//	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
//
//	Position(pos);
//	Scale(scale);
//
//}
//
//// �f�X�g���N�^
//CNumberFloor1::~CNumberFloor1()
//{
//	SAFE_DELETE(mpColliderMesh);
//}